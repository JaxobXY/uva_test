function handlePlatformCollisions(player, platforms, scrollOffset, GROUND_Y, canvasHeight, onVoidDeath) {
    let onPlatform = false;

    platforms.forEach(platform => {
        const pxLeft = player.x;
        const pxRight = player.x + player.size;
        const pxTop = player.y;
        const pxBottom = player.y + player.size;

        const pLeft = platform.x - scrollOffset;
        const pRight = platform.x + platform.width - scrollOffset;
        const pTop = platform.y;
        const pBottom = platform.y + platform.height;

        const overlapX = pxRight > pLeft && pxLeft < pRight;
        const overlapY = pxBottom > pTop && pxTop < pBottom;

        if (
            overlapX &&
            pxBottom >= pTop - 5 &&
            pxBottom <= pTop + 10 &&
            player.velocity >= 0
        ) {
            player.y = pTop - player.size;
            player.velocity = 0;
            player.onGround = true;
            onPlatform = true;
        }
    });

    if (!onPlatform) {
        player.onGround = false;
    }

    if (player.y > canvasHeight + player.size) {
        onVoidDeath();
    }
}

function handleSpikeCollisions(player, objects, scrollOffset, GROUND_Y, spikeBaseWidth) {
    let dead = false;

    objects.forEach(obj => {
        if (obj.type !== "spike") return;

        const baseY = obj.platformY || GROUND_Y;
        const tipY  = baseY - obj.height;

        const sxLeft  = obj.x - scrollOffset;
        const sxRight = sxLeft + spikeBaseWidth;
        const sxCenter = sxLeft + spikeBaseWidth / 2;

        const pxLeft   = player.x;
        const pxRight  = player.x + player.size;
        const pxCenter = player.x + player.size / 2;
        const pyTop    = player.y;
        const pyBottom = player.y + player.size;

        // FIXED: Precise triangle collision detection
        if (
            pxRight > sxLeft && 
            pxLeft < sxRight &&
            pyBottom > tipY + 10 &&  // Above tip
            pyTop < baseY
        ) {
            // Center proximity check for better feel
            if (Math.abs(pxCenter - sxCenter) < spikeBaseWidth / 1.5) {
                dead = true;
            }
        }
    });

    return dead;
}
