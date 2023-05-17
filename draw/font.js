const ctx = new Canvas(1000, 1000);

const kk = 100;
let filename = 1;

function save() {
    ctx.save2Image(`d:/draw/png/${filename++}.png`)
}

var Heart = function (x, y) {
    this.x = x;
    this.y = y;
    this.vertices = [];
    for (let i = 0; i < kk; i++) {
        var step = i / kk * (Math.PI * 2);
        var vector = {
            x: (15 * Math.pow(Math.sin(step), 3)) * 15,
            y: -(13 * Math.cos(step) - 5 * Math.cos(2 * step) - 2 * Math.cos(3 * step) - Math.cos(4 * step)) * 15
        }
        this.vertices.push(vector);
    }
}
Heart.prototype.draw = function () {
    ctx.beginPath();
    ctx.moveTo(this.x, this.y);
    ctx.fillStyle = 0xffff0000;
    for (let i = 0; i < kk; i++) {
        var vector = this.vertices[i];
        ctx.lineTo(vector.x + this.x, vector.y + this.y);
    }
    ctx.stroke();
}

ctx.hello = 1

var heart = new Heart(500, 500);
heart.draw();
save();





