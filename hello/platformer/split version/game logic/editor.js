let editorMouseDown = false;

canvas.addEventListener('mousedown', e => {
  if (mode !== "editor") return;
  if (e.button !== 0) return;
  editorMouseDown = true;
  editorClick(e);
});
canvas.addEventListener('mouseup', () => {
  editorMouseDown = false;
});
canvas.addEventListener('mousemove', e => {
  if (mode !== "editor" || !editorMouseDown) return;
  editorClick(e);
});

function screenToWorld(mx, my) {
  const viewWidth  = canvas.width  / cameraZoom;
  const viewHeight = canvas.height / cameraZoom;

  const worldX = (mx - canvas.width / 2) / cameraZoom + (cameraX + viewWidth  / 2);
  const worldY = (my - canvas.height / 2) / cameraZoom + (cameraY + viewHeight / 2);
  return { x: worldX, y: worldY };
}

function findMoverAtTile(map, tx, ty) {
  const wx = tx * tileSize;
  const wy = ty * tileSize;
  return map.movers.find(mv => mv.x === wx && mv.y === wy);
}

function findRotatorAtTile(map, tx, ty) {
  const wx = tx * tileSize;
  const wy = ty * tileSize;
  return map.rotators.find(rt => rt.x === wx && rt.y === wy);
}

function editorClick(e) {
  const rect = canvas.getBoundingClientRect();
  const mx = e.clientX - rect.left;
  const my = e.clientY - rect.top;

  const worldPos = screenToWorld(mx, my);
  const tx = Math.floor(worldPos.x / tileSize);
  const ty = Math.floor(worldPos.y / tileSize);

  if (tx < 0 || tx >= tilesWide || ty < 0 || ty >= tilesHigh) return;

  const m = currentMap();

  if (!gluePlacement || (!activeMover && !activeRotator)) {
    const savedMoverGroups = new Map();
    for (const mv of m.movers) {
      const key = `M:${mv.originTx},${mv.originTy}`;
      savedMoverGroups.set(key, mv.groupTiles);
    }
    const savedRotGroups = new Map();
    for (const rt of m.rotators) {
      const key = `R:${rt.originTx},${rt.originTy}`;
      savedRotGroups.set(key, rt.groupTiles);
    }

    m.mapChars[ty][tx] = currentTileType;
    rebuildObjectsFromMap(m);

    for (const mv of m.movers) {
      const key = `M:${mv.originTx},${mv.originTy}`;
      if (savedMoverGroups.has(key)) mv.groupTiles = savedMoverGroups.get(key);
    }
    for (const rt of m.rotators) {
      const key = `R:${rt.originTx},${rt.originTy}`;
      if (savedRotGroups.has(key)) rt.groupTiles = savedRotGroups.get(key);
    }

    activeMover = null;
    activeRotator = null;

    if (currentTileType === 'M') {
      const mv = findMoverAtTile(m, tx, ty);
      if (mv) { activeMover = mv; gluePlacement = true; }
    } else if (currentTileType === 'R') {
      const rt = findRotatorAtTile(m, tx, ty);
      if (rt) { activeRotator = rt; gluePlacement = true; }
    } else {
      const mv = findMoverAtTile(m, tx, ty);
      const rt = findRotatorAtTile(m, tx, ty);
      if (mv) { activeMover = mv; gluePlacement = true; }
      else if (rt) { activeRotator = rt; gluePlacement = true; }
    }
  } else {
    let obj = activeMover || activeRotator;
    const rootTx = obj.originTx;
    const rootTy = obj.originTy;
    const dx = tx - rootTx;
    const dy = ty - rootTy;

    if (!obj.groupTiles) {
      obj.groupTiles = [{ dx: 0, dy: 0, ch: obj === activeMover ? 'M' : 'R' }];
    }
    const existing = obj.groupTiles.find(t => t.dx === dx && t.dy === dy);

    if (currentTileType === '.') {
      if (existing && !(dx === 0 && dy === 0)) {
        obj.groupTiles = obj.groupTiles.filter(t => t !== existing);
      }
    } else {
      if (dx === 0 && dy === 0) {
        obj.groupTiles[0].ch = (obj === activeMover ? 'M' : 'R');
      } else if (existing) {
        existing.ch = currentTileType;
      } else {
        obj.groupTiles.push({ dx, dy, ch: currentTileType });
      }
    }
  }
}

// Buttons for mode/map/clear
playBtn.onclick = () => {
  mode = "game";
  editorUI.style.display = "none";
  gluePlacement = false;
  activeMover = null;
  activeRotator = null;
  resetPlayer();

  const m = currentMap();

  const savedMoverGroups = new Map();
  for (const mv of m.movers) {
    const key = `M:${mv.originTx},${mv.originTy}`;
    savedMoverGroups.set(key, mv.groupTiles || [{ dx: 0, dy: 0, ch: 'M' }]);
  }
  const savedRotGroups = new Map();
  for (const rt of m.rotators) {
    const key = `R:${rt.originTx},${rt.originTy}`;
    savedRotGroups.set(key, rt.groupTiles || [{ dx: 0, dy: 0, ch: 'R' }]);
  }

  rebuildObjectsFromMap(m);

  for (const mv of m.movers) {
    const key = `M:${mv.originTx},${mv.originTy}`;
    if (savedMoverGroups.has(key)) mv.groupTiles = savedMoverGroups.get(key);
    mv.curX = mv.x;
    mv.curY = mv.y;
    mv.prevX = mv.x;
    mv.prevY = mv.y;
    mv.phase = 0;
  }
  for (const rt of m.rotators) {
    const key = `R:${rt.originTx},${rt.originTy}`;
    if (savedRotGroups.has(key)) rt.groupTiles = savedRotGroups.get(key);
    rt.curX = rt.x;
    rt.curY = rt.y;
    rt.prevX = rt.x;
    rt.prevY = rt.y;
    rt.phase = 0;
  }
};

editorBtn.onclick = () => {
  mode = "editor";
  editorUI.style.display = "block";
  player.vx = 0;
  player.vy = 0;
};

clearBtn.onclick = () => {
  const m = currentMap();
  for (let y = 0; y < tilesHigh; y++) {
    for (let x = 0; x < tilesWide; x++) {
      m.mapChars[y][x] = '.';
    }
  }
  for (let x = 0; x < tilesWide; x++) m.mapChars[tilesHigh - 1][x] = '#';
  rebuildObjectsFromMap(m);
  activeMover = null;
  activeRotator = null;
  gluePlacement = false;
};

prevMapBtn.onclick = () => {
  currentMapIndex = (currentMapIndex - 1 + maps.length) % maps.length;
  resetPlayer();
  activeMover = null;
  activeRotator = null;
  gluePlacement = false;
  updateMapLabel();
};

nextMapBtn.onclick = () => {
  currentMapIndex = (currentMapIndex + 1) % maps.length;
  resetPlayer();
  activeMover = null;
  activeRotator = null;
  gluePlacement = false;
  updateMapLabel();
};

function updateEditorFly() {
  const flySpeed = 6;

  let vx = 0;
  let vy = 0;
  if (input.left)  vx -= flySpeed;
  if (input.right) vx += flySpeed;
  if (input.jump)  vy -= flySpeed;
  if (input.down)  vy += flySpeed;

  player.x += vx;
  player.y += vy;

  if (player.x < 0) player.x = 0;
  if (player.y < 0) player.y = 0;
  if (player.x + player.w > levelWidth)  player.x = levelWidth  - player.w;
  if (player.y + player.h > levelHeight) player.y = levelHeight - player.h;
}
