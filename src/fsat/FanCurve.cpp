#include <fsat/FanCurve.h>
#include <cmath>

//CurveConditions::CurveConditions(double density, double rpm, double barometricPressure, double isentropicExponent)
//		: density(density), rpm(rpm), barometricPressure(barometricPressure), isentropicExponent(isentropicExponent)
//{
//
//}


std::vector<ResultData> FanCurve::calculate()
{
//	this->resultData.clear();
	std::vector<ResultData> results;
	for (auto const & row : this->curveData.data) {
		double kp = 1, kpC = 1;
		double estPt, estPtc;
		for (auto i = 0; i < 7; i++) {
			auto saveKpOverKpc = kp / kpC;
			auto const qC = row.flow * (this->efficiencyCorrected / this->efficiency) * (kp / kpC); // eq 17

			auto const v1 = row.flow / this->area1; // eq 32, TODO row.flow == Q1? see page 58
			auto const pv1 = this->density * std::pow(v1 / 1096, 2); // eq 33
			auto const v2 = row.flow / this->area2;
			auto const pv2 = this->density * std::pow(v2 / 1096, 2);
			// if this->area1, this->area2 blank doesn't apply here, but for now the logic will be if they are negative
			if (this->area1 < 0 || this->area2 < 0) {
				estPt = row.pressure; // TODO needs further analysis, this is likely wrong.
			} else {
				switch (this->curveData.curveType) {
					case FanCurveType::FanStaticPressure: {
						estPt = row.pressure + pv2;
						break;
					}
					case FanCurveType::StaticPressureRise: {
						estPt = row.pressure + pv2 - pv1;
						break;
					}
					case FanCurveType::FanTotalPressure: {
						estPt = row.pressure;
						break;
					}
				}
			}

			// TODO qC, efficiency (N) , hC and pBoxC should be outputs (pBoxC is based on FanCurveType)

			// eq 18, 19 and 20 depend on the type of FanCurve, here pressure (row.pressure) represents the pressure type?
			auto const pBoxC = row.pressure * std::pow(this->efficiencyCorrected / this->efficiency, 2) *
			                   (this->densityCorrected / this->density) * (kp / kpC);
			estPtc = estPt * std::pow(this->efficiencyCorrected / this->efficiency, 2) *
			         (this->densityCorrected / this->density) * (kp / kpC);
			auto const hC = row.power * std::pow(this->efficiencyCorrected / this->efficiency, 3) *
			                (this->densityCorrected / this->density) * (kp / kpC);
			auto const pt1 = this->pt1Factor * estPt; // see page 54 section 4.1.13
			auto const x = estPt / (pt1 + 13.63 * this->pressureBarometric); // eq 25 see pg 54
			auto const z = ((this->gamma - 1) / this->gamma) * (6362 * row.power / row.flow) /
			               (pt1 + 13.63 * this->pressureBarometric); // TODO might be wrong see page 55
			kp = (std::log(1 + x) / x) * (z / (std::log(1 + z))); // eq 27
			auto const pt1c = this->pt1Factor * estPtc; // eq 28
			auto const xc = estPtc / (pt1c + 13.63 * this->pressureBarometricCorrected); // eq 29
			auto const zc = ((this->gammaCorrected - 1) / this->gammaCorrected) * (6362 * hC / qC) / (pt1c + 13.63 *
			                                                                                                 this->pressureBarometricCorrected); // eq 30, TODO number is off significantly, but why?
			kpC = (std::log(1 + xc) / xc) * (zc / (std::log(1 + zc))); // eq 31
			auto const efficiency = (row.flow * row.pressure * kp) / (6362 * row.power);

			// TODO is LHS supposed to be estPtc or ptc? see page 61 eq 38
			// TODO SERIOUS - if does not converge, a results entry will not exist for that particular row of input data - ask about this
			if (std::abs(saveKpOverKpc - kp / kpC) < 0.00001) {
				results.emplace_back(ResultData(qC, pBoxC, hC, efficiency));
				break;
			}
			if (!row.flow) {
				results.emplace_back(ResultData(0, pBoxC, hC, 0));
				break;
			}
		}
	}
	return results;
}
