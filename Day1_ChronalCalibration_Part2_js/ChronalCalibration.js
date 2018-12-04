const readline = require('readline');
const fs = require('fs');

let frequency = 0;
let seenFrequencies = [];
seenFrequencies[frequency] = true;

function readFile() {
    const rl = readline.createInterface({
        input: fs.createReadStream('input.txt'),
        crlfDelay: Infinity
    });

    rl.on('line', (line) => {
        let offset = parseInt(line);
        frequency += offset;
        if (seenFrequencies[frequency]) {
            process.stdout.write(frequency.toString());
            process.exit();
        }
        seenFrequencies[frequency] = true;
    });

    rl.on('close', () => {
        readFile();
    });
}

readFile();
