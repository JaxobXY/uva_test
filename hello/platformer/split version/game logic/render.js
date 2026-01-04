function drawWorldAndPlayer() {
  const m = currentMap();

  ctx.setTransform(1, 0, 0, 1, 0, 0);
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  ctx.save();

  const viewWidth  = canvas.width  / cameraZoom;
  const viewHeight = canvas.height / cameraZoom;

  ctx.translate(canvas.width / 2, canvas.height / 2);
  ctx.scale(cameraZoom, cameraZoom);
  ctx.translate(-(cameraX + viewWidth / 2), -(cameraY + viewHeight / 2));

  ctx.fillStyle = "#222";
  ctx.fillRect(0, 0, levelWidth, levelHeight);

  ctx.fillStyle = "#555";
  for (const p of m.platforms) {
    ctx.fillRect(p.x, p.y, p.w, p.h);
  }

  for (const lock of m.locks) {
    if (!lock.open) {
      ctx.fillStyle = "#8844ff";
      ctx.fillRect(lock.x, lock.y, lock.w, lock.h);
    }
  }

  for (const key of m.keys) {
    if (!key.collected) {
      ctx.fillStyle = "#ffd700";
      ctx.fillRect(key.x + 5, key.y + 5, key.w - 10, key.h - 10);
    }
  }

  for (const pad of m.jumpPads) {
    ctx.fillStyle = "#00bfff";
    ctx.fillRect(pad.x, pad.y, pad.w, pad.h);
  }

  for (const portal of m.portals) {
    ctx.fillStyle = "#00ff88";
    ctx.fillRect(portal.x, portal.y, portal.w, portal.h);
  }

  ctx.fillStyle = "#ff4444";
  for (const s of m.spikes) {
    ctx.beginPath();
    const baseY = s.y + s.h;
    ctx.moveTo(s.x, baseY);
    ctx.lineTo(s.x + s.w / 2, s.y);
    ctx.lineTo(s.x + s.w, baseY);
    ctx.closePath();
    ctx.fill();
  }

  ctx.fillStyle = "#aaaa00";
  for (const p of m.pistons) {
    ctx.fillRect(p.x, p.y, p.w, p.h);
  }

  // Movers
  for (const mv of m.movers) {
    for (const t of mv.groupTiles) {
      const tx = mv.curX + t.dx * tileSize;
      const ty = mv.curY + t.dy * tileSize;
      let color = "#ff8800";
      if (t.ch === '#') color = "#555";
      else if (t.ch === 'S') color = "#ff4444";
      else if (t.ch === 'K') color = "#ffd700";
      else if (t.ch === 'L') color = "#8844ff";
      else if (t.ch === 'J') color = "#00bfff";
      else if (t.ch === 'P') color = "#00ff88";
      else if (t.ch === 'T') color = "#aaaa00";
      ctx.fillStyle = color;

      if (t.ch === 'S') {
        ctx.beginPath();
        const baseY2 = ty + tileSize;
        ctx.moveTo(tx, baseY2);
        ctx.lineTo(tx + tileSize / 2, ty);
        ctx.lineTo(tx + tileSize, baseY2);
        ctx.closePath();
        ctx.fill();
      } else {
        ctx.fillRect(tx, ty, tileSize, tileSize);
      }
    }
  }

  // Rotators
  for (const rt of m.rotators) {
    const baseX = rt.curX;
    const baseY = rt.curY;
    const cx = baseX + rt.w / 2;
    const cy = baseY + rt.h / 2;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(rt.angle);
    ctx.translate(-cx, -cy);

    for (const t of rt.groupTiles) {
      const tx = baseX + t.dx * tileSize;
      const ty = baseY + t.dy * tileSize;
      let color = "#ff8800";
      if (t.ch === '#') color = "#555";
      else if (t.ch === 'R') color = "#ff8800";
      else if (t.ch === 'S') color = "#ff4444";
      else if (t.ch === 'K') color = "#ffd700";
      else if (t.ch === 'L') color = "#8844ff";
      else if (t.ch === 'J') color = "#00bfff";
      else if (t.ch === 'P') color = "#00ff88";
      else if (t.ch === 'T') color = "#aaaa00";
      ctx.fillStyle = color;

      if (t.ch === 'S') {
        ctx.beginPath();
        const baseY2 = ty + tileSize;
        ctx.moveTo(tx, baseY2);
        ctx.lineTo(tx + tileSize / 2, ty);
        ctx.lineTo(tx + tileSize, baseY2);
        ctx.closePath();
        ctx.fill();
      } else {
        ctx.fillRect(tx, ty, tileSize, tileSize);
      }
    }

    ctx.restore();
  }

  // Player
  ctx.fillStyle = mode === "editor" ? "#ff00ff" : "#0f0";
  ctx.fillRect(player.x, player.y, player.w, player.h);

  ctx.restore();
}
