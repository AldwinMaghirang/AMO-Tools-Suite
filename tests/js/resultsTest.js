/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psat', function (t) {
    t.plan(2);
    t.type(bindings.results, 'function');
    var inp = {};
    // Pump Style End suction ansi API
    inp.pump_style = 6;
    inp.motor_rated_speed = 1780;
    inp.line = 1;
    // Either specify an efficiency class OR provide efficiency percentage
    inp.efficiency_class = 1;
    inp.efficiency = 0;
    inp.motor_rated_voltage = 460;
    var res = bindings.results(inp);
    t.equal(res, 225.800612262395, 'res is ' + res);

});