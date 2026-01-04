function updateMovers() {
  const m = currentMap();
  const moveSpd = 0.03;

  for (const mv of m.movers) {
    mv.prevX = mv.curX;
    mv.prevY = mv.curY;

    mv.phase += moveSpd;
    const offset = Math.sin(mv.phase) * mv.pushDist;
    mv.curX = mv.x + offset;
    mv.curY = mv.y;

    mv.originTx = Math.round(mv.curX / tileSize);
    mv.originTy = Math.round(mv.curY / tileSize);
  }
}

function updateRotators() {
  const m = currentMap();
  for (const rt of m.rotators) {
    rt.prevX = rt.curX;
    rt.prevY = rt.curY;

    rt.phase += rt.speed;
    rt.angle = rt.phase;
    rt.curX = rt.x;
    rt.curY = rt.y;
  }
}

function updateGame() {
  const m = currentMap();

  updateMovers();
  updateRotators();

  // Carrier logic
  let carrierDx = 0, carrierDy = 0;
  const feetRect = {
    x: player.x,
    y: player.y + player.h,
    w: player.w,
    h: 1
  };

  for (const mv of m.movers) {
    if (!mv.groupTiles) continue;
    const dxMv = mv.curX - mv.prevX;
    const dyMv = mv.curY - mv.prevY;
    if (dxMv === 0 && dyMv === 0) continue;

    for (const t of mv.groupTiles) {
      if (t.ch === '.' || t.ch === 'S' || t.ch === 'J' || t.ch === 'P') continue;
      const rect = {
        x: mv.curX + t.dx * tileSize,
        y: mv.curY + t.dy * tileSize,
        w: tileSize,
        h: tileSize
      };
      const floorRect = { x: rect.x, y: rect.y - 1, w: rect.w, h: rect.h + 1 };
      if (rectsOverlap(feetRect, floorRect)) {
        carrierDx = dxMv;
        carrierDy = dyMv;
        break;
      }
    }
    if (carrierDx || carrierDy) break;
  }

  if (carrierDx || carrierDy) {
    player.x += carrierDx;
    player.y += carrierDy;
  }

  // Crushing / pushing by movers
  for (const mv of m.movers) {
    if (!mv.groupTiles) continue;
    const dxMv = mv.curX - mv.prevX;
    const dyMv = mv.curY - mv.prevY;
    if (dxMv === 0 && dyMv === 0) continue;

    for (const t of mv.groupTiles) {
      if (t.ch === '.' || t.ch === 'S' || t.ch === 'J' || t.ch === 'P') continue;

      const rect = {
        x: mv.curX + t.dx * tileSize,
        y: mv.curY + t.dy * tileSize,
        w: tileSize,
        h: tileSize
      };

      if (rectsOverlap(player, rect)) {
        if (dxMv !== 0) {
          player.x += dxMv;
        }
        if (dyMv !== 0) {
          player.y += dyMv;
        }
      }
    }
  }

  // Input → velocity
  if (player.knockTime > 0) player.knockTime--;

  if (player.knockTime <= 0) {
    player.vx = 0;
    if (input.left)  player.vx = -moveSpeed;
    if (input.right) player.vx =  moveSpeed;
  }

  // Crouch / stand
  const oldH = player.h;
  if (input.down && player.knockTime <= 0) {
    player.h = crouchHeight;
  } else {
    const solids = getSolids();
    const standRect = {
      x: player.x,
      y: player.y - (basePlayerHeight - player.h),
      w: player.w,
      h: basePlayerHeight
    };
    let blocked = false;
    for (const s of solids) {
      if (rectsOverlap(standRect, s)) { blocked = true; break; }
    }
    if (!blocked) {
      player.y = standRect.y;
      player.h = basePlayerHeight;
    }
  }
  if (player.h < oldH) {
    player.y += (oldH - player.h);
  }

  // Jumps
  const jumpInput = input.jump;
  jumpPressed = jumpInput && !prevJumpInput;
  prevJumpInput = jumpInput;

  if (jumpPressed && player.knockTime <= 0) {
    if (player.onGround && player.jumpsUsed === 0) {
      player.vy = jumpStrength;
      player.onGround = false;
      player.jumpsUsed = 1;
    } else if (!player.onGround && player.jumpsUsed < player.maxJumps) {
      player.vy = jumpStrength;
      player.jumpsUsed++;
    }
  }

  // Gravity
  player.vy += gravity;

  // Collision X
  const solidsX = getSolids();

  player.x += player.vx;
  for (const s of solidsX) {
    if (rectsOverlap(player, s)) {
      if (player.vx > 0) player.x = s.x - player.w;
      else if (player.vx < 0) player.x = s.x + s.w;
    }
  }

  // Collision Y
  player.y += player.vy;
  player.onGround = false;
  const solidsY = getSolids();
  for (const s of solidsY) {
    if (rectsOverlap(player, s)) {
      const overlapBottom = (player.y + player.h) - s.y;
      const overlapTop    = (s.y + s.h) - player.y;

      if (player.vy > 0 && overlapBottom <= overlapTop) {
        player.y = s.y - player.h;
        player.vy = 0;
        player.onGround = true;
        player.jumpsUsed = 0;
      } else if (player.vy < 0 && overlapTop < overlapBottom) {
        player.y = s.y + s.h;
        player.vy = 0;
      }
    }
  }

  // World bounds
  if (player.x < 0) player.x = 0;
  if (player.x + player.w > levelWidth) player.x = levelWidth - player.w;
  if (player.y + player.h > levelHeight) {
    player.y = levelHeight - player.h;
    player.vy = 0;
    player.onGround = true;
    player.jumpsUsed = 0;
  }

  const m2 = currentMap();

  // Keys / locks
  for (const key of m2.keys) {
    if (!key.collected && rectsOverlap(player, key)) {
      key.collected = true;
    }
  }
  for (const lock of m2.locks) {
    if (!lock.open) {
      const key1 = m2.keys.find(k => k.id === lock.id);
      if (key1 && key1.collected) lock.open = true;
    }
  }

  // Jump pads
  for (const pad of m2.jumpPads) {
    const feet = {
      x: player.x,
      y: player.y + player.h,
      w: player.w,
      h: 1
    };
    if (rectsOverlap(feet, pad) && player.vy >= 0) {
      player.vy = pad.power;
      player.onGround = false;
      player.jumpsUsed = 1;
    }
  }

  // Portals
  for (let i = 0; i < m2.portals.length; i++) {
    const portal = m2.portals[i];
    if (portal.cooldown > 0) portal.cooldown--;

    if (portal.cooldown === 0 && rectsOverlap(player, portal) && portal.targetIndex !== -1) {
      const target = m2.portals[portal.targetIndex];
      if (target && target !== portal) {
        player.x = target.x + target.w / 2 - player.w / 2;
        player.y = target.y - player.h;
        portal.cooldown = 20;
        target.cooldown = 20;
        break;
      }
    }
  }

  // Spikes
  for (const s of m2.spikes) {
    if (rectsOverlap(player, s)) {
      resetPlayer();
      break;
    }
  }

  // Pistons
  const pushTiles = 4;
  const pushSpeed = (pushTiles * tileSize) / 10;
  if (player.knockTime <= 0) {
    for (const p of m2.pistons) {
      if (rectsOverlap(player, p)) {
        if (player.x + player.w / 2 < p.x + p.w / 2) {
          player.vx = -pushSpeed;
        } else {
          player.vx =  pushSpeed;
        }
        player.knockTime = 10;
        break;
      }
    }
  }

  // Rotator tiles (spikes / jump pads on rotators)
  for (const rt of m2.rotators) {
    if (!rt.groupTiles) continue;
    for (const t of rt.groupTiles) {
      const rect = getGroupTileWorldRectRot(rt, t);
      if (t.ch === 'S') {
        if (rectsOverlap(player, rect)) {
          resetPlayer();
          break;
        }
      } else if (t.ch === 'J') {
        const feet = {
          x: player.x,
          y: player.y + player.h,
          w: player.w,
          h: 1
        };
        if (rectsOverlap(feet, rect) && player.vy >= 0) {
          player.vy = -22;
          player.onGround = false;
          player.jumpsUsed = 1;
        }
      }
    }
  }
}
