// Read file
const fs = require('node:fs');

fs.readFile('./FLOPS_DP.log', 'utf8', (err, data) => {
  if (err) {
    console.error(err);
    return;
  }
    data = data.split("/**/");
    const first = data[0];
    const second = data[1];

    const FP = second.match(/(^.*?DP MFLOP.*\n)(.*?$)/gm).map(s => parseFloat(s.split("|").join().split("\n").join().split(",,,")[0].trim().split(",")[2].trim()));
    //FP_ARITH_INST_RETIRED_SCALAR_DOUBLE
    console.log(FP);
  
});


// After the third -------------------------------------------------------------------------------- change out put