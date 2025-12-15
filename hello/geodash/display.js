// display.js

function drawBackgroundGrid(ctx, canvas) {
    ctx.strokeStyle = "#00ffff";
    ctx.lineWidth = 1;
    ctx.shadowBlur = 10;
    ctx.shadowColor = "#00ffff";

    for (let x = 0; x < canvas.width; x += 50) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, canvas.height);
        ctx.stroke();
    }
    ctx.shadowBlur = 0;
}

function drawPlatforms(ctx, platforms, scrollOffset) {
    ctx.fillStyle = "#ff00ff";
    ctx.shadowBlur = 40;
    ctx.shadowColor = "#ff00ff";

    platforms.forEach(platform => {
        const screenX = platform.x - scrollOffset;
        if (screenX + platform.width > -100 && screenX < ctx.canvas.width + 100) {
            ctx.fillRect(screenX, platform.y, platform.width, platform.height);
        }
    });
    ctx.shadowBlur = 0;
}

function drawPlatformEdges(ctx, platforms, scrollOffset) {
    ctx.strokeStyle = "#ffffff";
    ctx.lineWidth = 2;
    ctx.shadowBlur = 15;
    ctx.shadowColor = "#ffffff";

    platforms.forEach(platform => {
        const screenX = platform.x - scrollOffset;
        if (screenX + platform.width > -100 && screenX < ctx.canvas.width + 100) {
            ctx.strokeRect(screenX, platform.y, platform.width, platform.height);
        }
    });
    ctx.shadowBlur = 0;
}

function drawNeonGlow(ctx, x, y, w, h, color, blurSize = 30) {
    ctx.shadowBlur = blurSize;
    ctx.shadowColor = color;
    ctx.fillStyle = color;
    ctx.fillRect(x, y, w, h);
    ctx.shadowBlur = 0;
}

function drawNeonTriangle(ctx, x1, y1, x2, y2, x3, y3, color, glowSize = 25) {
    ctx.shadowBlur = glowSize;
    ctx.shadowColor = color;
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.lineTo(x3, y3);
    ctx.closePath();
    ctx.fill();
    ctx.shadowBlur = 0;
}

function drawPlayer(ctx, player) {
    drawNeonGlow(ctx, player.x, player.y, player.size, player.size, "#00ff00", 35);
}

function drawSpikes(ctx, objects, scrollOffset, GROUND_Y, spikeBaseWidth) {
    objects.forEach(obj => {
        if (obj.type !== "spike") return;

        const baseY = obj.platformY || GROUND_Y;   // platform top
        const tipY  = baseY - obj.height;
        const screenX = obj.x - scrollOffset;

        if (screenX + spikeBaseWidth > -50 && screenX < ctx.canvas.width + 50) {
            drawNeonTriangle(
                ctx,
                screenX, baseY,
                screenX + spikeBaseWidth / 2, tipY,
                screenX + spikeBaseWidth, baseY,
                "#ff0080",
                30
            );
        }
    });
}

function drawParticles(ctx) {
    if (!window.particles) return;
    window.particles.forEach(p => {
        ctx.save();
        ctx.globalAlpha = p.life;
        ctx.shadowBlur = 20 * p.life;
        ctx.shadowColor = p.color;
        ctx.fillStyle = p.color;
        ctx.beginPath();
        ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
    });
}
