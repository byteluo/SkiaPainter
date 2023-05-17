const ctx = new Canvas(1000, 1000);

const start = new Date();

for (let i = 0; i < 10000; i++) {
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.lineTo(500, 500);
    ctx.moveTo(500, 0);
    ctx.rect(200, 200, 100, 100);
    ctx.stroke();
    ctx.fillText("hello world", 200, 100);
}

LOG(new Date() - start);

ctx.save("d:/performance.png");