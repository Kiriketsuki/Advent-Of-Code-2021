const fs =  require('fs');
const path = require('path');
const inputPath = path.join(__dirname, 'input.txt');

const text = fs.readFileSync(inputPath, 'utf8');
var input = text.replace(/\r/g, '').split('\n');

console.log(input[0]);

// forward adds to horizontal, no backwards
// up and down adds and subtracts from depth
// * assuming proper formatting because i am too lazy to check

var horizontal = 0;
var depth = 0;
// part 1
for (var i = 0; i < input.length; i++) {
    var element = input[i].split(' ');
    var direction = element[0];
    var distance = parseInt(element[1]);
    switch (direction) {
        case 'forward':
            horizontal += distance;
            break;
        case 'back':
            horizontal -= distance;
            break;
        case 'up':
            depth -= distance;
            break;
        case 'down':
            depth += distance;
            break;
        default:
            console.log(direction);
            break;
    }
}

console.log(horizontal * depth);

// part 2
var horizontal = 0;
var depth = 0;
var aim = 0;

for (var i = 0; i < input.length; i++) {
    var element = input[i].split(' ');
    var direction = element[0];
    var distance = parseInt(element[1]);
    switch (direction) {
        case 'forward':
            horizontal += distance;
            depth += distance * aim;
            break;
        case 'back':
            horizontal -= distance;
            depth -= distance * aim;
            break;
        case 'up':
            aim -= distance;
            break;
        case 'down':
            aim += distance;
            break;
        default:
            console.log(direction);
            break;
    }
}

console.log(horizontal * depth);