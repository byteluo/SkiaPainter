const canvas = new Canvas(500, 500);


canvas.beginPath();
canvas.moveTo(0, 0);
canvas.lineTo(100, 100);
canvas.moveTo(200, 200);

canvas.setLineWidth(20);
canvas.rect(200, 200, 100, 100);
canvas.stroke();

canvas.save2Image("d:/draw/path.png");