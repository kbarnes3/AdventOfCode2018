const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
    input: fs.createReadStream('input.txt'),
    crlfDelay: Infinity
});

let frequency = 0;

rl.on('line', (line) => {
    let offset = parseInt(line);
    frequency += offset;
});

rl.on('close', () => {
    process.stdout.write(frequency.toString());
});
