const basePlayerWidth  = tileSize;
const basePlayerHeight = tileSize;
const crouchHeight     = tileSize * 0.6;

const player = {
  x: 2 * tileSize,
  y: (tilesHigh - 4) * tileSize,
  w: basePlayerWidth,
  h: basePlayerHeight,
  vx: 0,
  vy: 0,
  onGround: false,
  jumpsUsed: 0,
  maxJumps: 2,
  knockTime: 0
};

function resetPlayer() {
  player.x = 2 * tileSize;
  player.y = (tilesHigh - 4) * tileSize;
  player.vx = 0;
  player.vy = 0;
  player.onGround = false;
  player.jumpsUsed = 0;
  player.knockTime = 0;
  player.w = basePlayerWidth;
  player.h = basePlayerHeight;
}

const gravity = 0.8;
const moveSpeed = 4;
const jumpStrength = -14;

let jumpPressed = false;
let prevJumpInput = false;

function rectsOverlap(a, b) {
  return (
    a.x < b.x + b.w &&
    a.x + a.w > b.x &&
    a.y < b.y + b.h &&
    a.y + a.h > b.y
  );
}

// Rotator tile bounding helper
function getGroupTileWorldRectRot(rot, t) {
  const baseX = rot.curX;
  const baseY = rot.curY;
  const cx = baseX + rot.w / 2;
  const cy = baseY + rot.h / 2;

  const tx = baseX + t.dx * tileSize + tileSize / 2;
  const ty = baseY + t.dy * tileSize + tileSize / 2;

  const dx = tx - cx;
  const dy = ty - cy;
  const cos = Math.cos(rot.angle);
  const sin = Math.sin(rot.angle);

  const rx = cx + dx * cos - dy * sin;
  const ry = cy + dx * sin + dy * cos;

  const pad = 0.5;
  return {
    x: rx - tileSize / 2 - pad,
    y: ry - tileSize / 2 - pad,
    w: tileSize + pad * 2,
    h: tileSize + pad * 2
  };
}

// All solid geometry
function getSolids() {
  const m = currentMap();
  const solids = [];
  for (const p of m.platforms) solids.push(p);
  for (const l of m.locks) if (!l.open) solids.push(l);

  for (const mv of m.movers) {
    for (const t of mv.groupTiles) {
      if (t.ch === '.' || t.ch === 'S' || t.ch === 'J' || t.ch === 'P') continue;
      solids.push({
        x: mv.curX + t.dx * tileSize,
        y: mv.curY + t.dy * tileSize,
        w: tileSize,
        h: tileSize
      });
    }
  }

  for (const rt of m.rotators) {
    for (const t of rt.groupTiles) {
      if (t.ch === '.' || t.ch === 'S' || t.ch === 'J' || t.ch === 'P') continue;
      solids.push(getGroupTileWorldRectRot(rt, t));
    }
  }

  return solids;
}
