const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
    input: fs.createReadStream('input.txt'),
    crlfDelay: Infinity
});

let twoLetters = 0;
let threeLetters = 0;

rl.on('line', (line) => {
    let seenLetters = {};
    for (let i in line) {
        if (line.hasOwnProperty(i)) {
            let letter = line[i];
            if (seenLetters[letter]) {
                seenLetters[letter]++;
            } else {
                seenLetters[letter] = 1;
            }
        }
    }

    let hasTwo = false;
    let hasThree = false;

    for (let key in seenLetters) {
        if (seenLetters.hasOwnProperty(key)) {
            let seen = seenLetters[key];
            if (seen === 2) {
                hasTwo = true;
            }
            else if (seen === 3) {
                hasThree = true;
            }
        }
    }

    if (hasTwo) {
        twoLetters++;
    }
    if (hasThree) {
        threeLetters++;
    }
});

rl.on('close', () => {
    let checksum = twoLetters * threeLetters;
    process.stdout.write(checksum.toString());
});
