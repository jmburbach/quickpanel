function interpolate(value, table) {
    var len = table.length;

    for (var i=0; i < len - 1; ++i) {
        var e1 = table[i],
            in1 = e1[0],
            out1 = e1[1];

        var e2 = table[i+1],
            in2 = e2[0],
            out2 = e2[1];

        if (value >= in1 && value <= in2) {
            var diff = value - in1;
            var diff_in = in2 - in1;
            var t = diff / diff_in;
            return out1 + t * (out2 - out1);
        }
    }
    return 0;
}
