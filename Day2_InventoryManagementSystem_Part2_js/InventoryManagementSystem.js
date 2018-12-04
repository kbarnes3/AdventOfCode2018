const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
    input: fs.createReadStream('input.txt'),
    crlfDelay: Infinity
});

let boxIds = [];

rl.on('line', (nextBoxId) => {
    for (let i = 0; i < boxIds.length; i++) {
        let candidateBoxId = boxIds[i];
        let differences = 0;

        for (let j = 0; j < nextBoxId.length; j++) {
            if (candidateBoxId[j] !== nextBoxId[j]) {
                differences++;
                if (differences >= 2) {
                    break;
                }
            }
        }

        if (differences === 1) {
            for (let j = 0; j < nextBoxId.length; j++) {
                if (candidateBoxId[j] === nextBoxId[j]) {
                    process.stdout.write(nextBoxId[j]);
                }
            }
            process.exit();
        }
    }

    boxIds.push(nextBoxId);
});

rl.on('close', () => {
    process.stdout.write('No close matches found');
});
