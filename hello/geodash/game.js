const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");

// Game state
let gameState = "menu";
let currentLevel = 1;
let maxLevel = 5;
let levelComplete = false;
let finishAnimTimer = 0;

// World constants
const groundY = 320;
const gravity = 0.7;
const jumpVelocity = -14;
const lowJumpMultiplier = 0.4;
const fallMultiplier = 0.25;
const scrollSpeed = 6;

// Player
const player = {
  x: 120,
  y: groundY - 40,
  w: 40,
  h: 40,
  vy: 0,
  onGround: true,
  jumping: false,
  jumpHeld: false
};

// LEVELS - Hand-crafted, no random!
const levels = {
  1: {
    name: "Tutorial",
    platforms: [
      { x: 500, y: 260, w: 120, h: 20 },
      { x: 900, y: 220, w: 140, h: 20 },
      { x: 1300, y: 280, w: 100, h: 20 },
      { x: 1700, y: 240, w: 160, h: 20 },
      { x: 2200, y: 260, w: 120, h: 20 },
      { x: 2600, y: 220, w: 140, h: 20 }
    ],
    spikes: [
      { x: 650, baseY: groundY, width: 40, height: 50 },
      { x: 1450, baseY: groundY, width: 40, height: 50 },
      { x: 1850, baseY: groundY, width: 40, height: 50 }
    ],
    finishX: 2800
  },
  2: {
    name: "Saw Blade Alley",
    platforms: [
      { x: 500, y: 240, w: 80, h: 20 },
      { x: 750, y: 280, w: 100, h: 20 },
      { x: 1100, y: 200, w: 120, h: 20 },
      { x: 1550, y: 260, w: 90, h: 20 },
      { x: 1900, y: 220, w: 110, h: 20 },
      { x: 2350, y: 280, w: 80, h: 20 },
      { x: 2700, y: 240, w: 100, h: 20 }
    ],
    spikes: [
      { x: 600, baseY: groundY, width: 40, height: 50 },
      { x: 850, baseY: groundY, width: 40, height: 50 },
      { x: 1300, baseY: groundY, width: 40, height: 50 },
      { x: 1700, baseY: groundY, width: 40, height: 50 },
      { x: 2150, baseY: groundY, width: 40, height: 50 },
      { x: 2500, baseY: groundY, width: 40, height: 50 }
    ],
    finishX: 2900
  },
  3: {
    name: "Double Jump",
    platforms: [
      { x: 500, y: 280, w: 60, h: 20 },
      { x: 700, y: 240, w: 70, h: 20 },
      { x: 950, y: 200, w: 80, h: 20 },
      { x: 1200, y: 260, w: 60, h: 20 },
      { x: 1400, y: 220, w: 70, h: 20 },
      { x: 1650, y: 180, w: 90, h: 20 },
      { x: 1950, y: 260, w: 60, h: 20 },
      { x: 2200, y: 240, w: 80, h: 20 }
    ],
    spikes: [
      { x: 580, baseY: groundY, width: 40, height: 50 },
      { x: 1050, baseY: groundY, width: 40, height: 50 },
      { x: 1300, baseY: groundY, width: 40, height: 50 },
      { x: 1550, baseY: groundY, width: 40, height: 50 },
      { x: 2050, baseY: groundY, width: 40, height: 50 },
      { x: 2350, baseY: groundY, width: 40, height: 50 }
    ],
    finishX: 2450
  },
  4: {
    name: "Spike Gauntlet",
    platforms: [
      { x: 500, y: 250, w: 100, h: 20 },
      { x: 850, y: 270, w: 80, h: 20 },
      { x: 1200, y: 230, w: 90, h: 20 },
      { x: 1550, y: 290, w: 70, h: 20 },
      { x: 1850, y: 210, w: 100, h: 20 },
      { x: 2200, y: 260, w: 80, h: 20 },
      { x: 2550, y: 240, w: 90, h: 20 }
    ],
    spikes: [
      { x: 600, baseY: groundY, width: 40, height: 50 },
      { x: 950, baseY: groundY, width: 40, height: 50 },
      { x: 1350, baseY: groundY, width: 40, height: 50 },
      { x: 1700, baseY: groundY, width: 40, height: 50 },
      { x: 2000, baseY: groundY, width: 40, height: 50 },
      { x: 2300, baseY: groundY, width: 40, height: 50 },
      { x: 2650, baseY: groundY, width: 40, height: 50 }
    ],
    finishX: 2800
  },
  5: {
    name: "Final Climb",
    platforms: [
      { x: 500, y: 260, w: 120, h: 20 },
      { x: 750, y: 220, w: 100, h: 20 },
      { x: 1050, y: 280, w: 80, h: 20 },
      { x: 1350, y: 200, w: 110, h: 20 },
      { x: 1700, y: 260, w: 90, h: 20 },
      { x: 2050, y: 220, w: 100, h: 20 },
      { x: 2400, y: 180, w: 120, h: 20 },
      { x: 2750, y: 260, w: 100, h: 20 }
    ],
    spikes: [
      { x: 650, baseY: groundY, width: 40, height: 50 },
      { x: 1150, baseY: groundY, width: 40, height: 50 },
      { x: 1450, baseY: groundY, width: 40, height: 50 },
      { x: 1850, baseY: groundY, width: 40, height: 50 },
      { x: 2200, baseY: groundY, width: 40, height: 50 },
      { x: 2550, baseY: groundY, width: 40, height: 50 }
    ],
    finishX: 2950
  }
};

let platforms = [];
let obstacles = [];
let spawnTimer = 0;
let score = 0;
let gameOver = false;
let finishX = 0;

// Reset functions
function resetPlayer() {
  player.x = 120;
  player.y = groundY - 40;
  player.vy = 0;
  player.onGround = true;
  player.jumping = false;
  player.jumpHeld = false;
}

function loadLevel(levelNum) {
  const level = levels[levelNum];
  platforms = level.platforms.map(p => ({...p}));
  obstacles = level.spikes.map(s => ({...s}));
  finishX = level.finishX;
  score = 0;
  levelComplete = false;
  finishAnimTimer = 0;
  gameOver = false;
  resetPlayer();
}

function hardResetToMenu() {
  currentLevel = 1;
  loadLevel(1);
  gameState = "menu";
}

function startGame() {
  loadLevel(currentLevel);
  gameState = "playing";
}

function nextLevel() {
  if (currentLevel < maxLevel) {
    currentLevel++;
    loadLevel(currentLevel);
  } else {
    // Game Complete!
    gameState = "complete";
  }
}

// ... (keep all the same physics/spike/triangle functions)
function pointInTriangle(px, py, ax, ay, bx, by, cx, cy) {
  const d = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy);
  if (d === 0) return false;
  const alpha = ((by - cy) * (px - cx) + (cx - bx) * (py - cy)) / d;
  const beta  = ((cy - ay) * (px - cx) + (ax - cx) * (py - cy)) / d;
  const gamma = 1 - alpha - beta;
  return alpha > 0 && beta > 0 && gamma > 0;
}

function playerInSpike(spike) {
  const corners = [
    { x: player.x, y: player.y },
    { x: player.x + player.w, y: player.y },
    { x: player.x, y: player.y + player.h },
    { x: player.x + player.w, y: player.y + player.h }
  ];
  const p1 = { x: spike.x, y: spike.baseY };
  const p2 = { x: spike.x + spike.width, y: spike.baseY };
  const p3 = { x: spike.x + spike.width / 2, y: spike.baseY - spike.height };

  for (const c of corners) {
    if (pointInTriangle(c.x, c.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y)) return true;
  }
  return false;
}

function applyAdvancedGravity() {
  player.vy += gravity;
  if (player.vy > 0) player.vy += gravity * fallMultiplier;
  else if (!player.jumpHeld && player.vy < 0) player.vy += gravity * lowJumpMultiplier;
}

function updatePlayer() {
  const prevY = player.y;

  applyAdvancedGravity();
  player.y += player.vy;
  player.onGround = false;

  if (player.y + player.h >= groundY) {
    player.y = groundY - player.h;
    player.vy = 0;
    player.onGround = true;
    player.jumping = false;
  }

  for (const p of platforms) {
    const horz = player.x + player.w > p.x && player.x < p.x + p.w;

    if (horz && prevY + player.h <= p.y && player.y + player.h >= p.y && player.vy >= 0) {
      const centerX = player.x + player.w / 2;
      if (centerX > p.x + 10 && centerX < p.x + p.w - 10) {
        player.y = p.y - player.h;
        player.vy = 0;
        player.onGround = true;
                player.jumping = false;
        continue;
      }
    }

    // Head bump
    if (horz && player.vy < 0 && player.y < p.y + p.h && prevY >= p.y + p.h - 1) {
      player.y = p.y + p.h;
      player.vy = 0;
    }
  }
}

function updateLevelElements() {
  // Scroll platforms and spikes
  for (const p of platforms) p.x -= scrollSpeed;
  for (const s of obstacles) s.x -= scrollSpeed;

  // Remove off-screen spikes and count score
  for (let i = obstacles.length - 1; i >= 0; i--) {
    if (obstacles[i].x + obstacles[i].width < 0) {
      obstacles.splice(i, 1);
      score++;
    }
  }

  // Check if player reached finish line
  if (player.x >= finishX - 100) {
    levelComplete = true;
    finishAnimTimer = 120; // 2 seconds @ 60fps
  }
}

function checkCollisions() {
  // Spikes
  for (const s of obstacles) {
    if (playerInSpike(s)) {
      gameOver = true;
      return;
    }
  }

  // Left side of platforms = death
  for (const p of platforms) {
    if (player.x + player.w > p.x && player.x < p.x + p.w &&
        player.y + player.h > p.y && player.y < p.y + p.h) {
      if (player.x + player.w / 2 < p.x + p.w / 2 - 15) {
        gameOver = true;
        return;
      }
    }
  }
}

// Drawing
function drawGround() {
  ctx.fillStyle = "#333";
  ctx.fillRect(0, groundY, canvas.width, canvas.height - groundY);
}

function drawPlatforms() {
  ctx.fillStyle = "#3bd1ff";
  for (const p of platforms) ctx.fillRect(p.x, p.y, p.w, p.h);
}

function drawPlayer() {
  ctx.fillStyle = "#ffcc00";
  ctx.fillRect(player.x, player.y, player.w, player.h);
  // Eyes
  ctx.fillStyle = "#000";
  ctx.fillRect(player.x + 8, player.y + 8, 8, 8);
  ctx.fillRect(player.x + 24, player.y + 8, 8, 8);
}

function drawObstacles() {
  for (const s of obstacles) {
    ctx.fillStyle = "#ff3b30";
    ctx.beginPath();
    ctx.moveTo(s.x, s.baseY);
    ctx.lineTo(s.x + s.width, s.baseY);
    ctx.lineTo(s.x + s.width / 2, s.baseY - s.height);
    ctx.closePath();
    ctx.fill();
  }
}

function drawFinishLine() {
  const fx = finishX;
  ctx.strokeStyle = "#00ff00";
  ctx.lineWidth = 6;
  ctx.setLineDash([10, 10]);
  ctx.beginPath();
  ctx.moveTo(fx, groundY - 200);
  ctx.lineTo(fx, groundY);
  ctx.stroke();
  ctx.setLineDash([]);

  // Glowing effect when close
  if (player.x > fx - 300) {
    const alpha = Math.min(1, (player.x - (fx - 300)) / 200);
    ctx.fillStyle = `rgba(0, 255, 0, ${alpha * 0.3})`;
    ctx.fillRect(fx - 100, groundY - 200, 200, 200);
  }
}

function drawHUD() {
  ctx.fillStyle = "#fff";
  ctx.font = "24px Arial";
  ctx.fillText(`Level ${currentLevel}: ${levels[currentLevel].name}`, 20, 40);
  ctx.fillText(`Score: ${score}`, 20, 74);

  if (gameOver) {
    ctx.fillStyle = "rgba(0,0,0,0.75)";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = "#ff3b30";
    ctx.font = "64px Arial";
    ctx.textAlign = "center";
    ctx.fillText("GAME OVER", canvas.width / 2, canvas.height / 2 - 30);
    ctx.fillStyle = "#fff";
    ctx.font = "28px Arial";
    ctx.fillText("Press R to return to menu", canvas.width / 2, canvas.height / 2 + 30);
    ctx.textAlign = "start";
  }

  if (levelComplete && finishAnimTimer > 0) {
    const alpha = Math.min(1, (120 - finishAnimTimer) / 60);
    ctx.fillStyle = `rgba(0, 255, 0, ${alpha})`;
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    ctx.fillStyle = "#fff";
    ctx.font = "72px Arial";
    ctx.textAlign = "center";
    ctx.fillText("LEVEL COMPLETE!", canvas.width / 2, canvas.height / 2);
    ctx.font = "32px Arial";
    ctx.fillText("Get ready...", canvas.width / 2, canvas.height / 2 + 60);
    ctx.textAlign = "start";
  }
}

function drawMenu() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  drawGround();
  drawPlatforms();
  drawPlayer();
  drawFinishLine();

  ctx.fillStyle = "#ffcc00";
  ctx.font = "56px Arial";
  ctx.textAlign = "center";
  ctx.fillText("Mini Geometry Dash", canvas.width / 2, 100);

  ctx.fillStyle = "#fff";
  ctx.font = "32px Arial";
  ctx.fillText(`Level ${currentLevel}: ${levels[currentLevel].name}`, canvas.width / 2, 160);

  ctx.font = "28px Arial";
  ctx.fillText("Press ENTER to start", canvas.width / 2, 240);
  ctx.fillText("SPACE = Jump (hold for higher)", canvas.width / 2, 290);
  ctx.fillText("R = Menu", canvas.width / 2, 330);
  ctx.textAlign = "start";
}

function drawGameComplete() {
  ctx.fillStyle = "#000";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  ctx.fillStyle = "#00ff00";
  ctx.font = "72px Arial";
  ctx.textAlign = "center";
  ctx.fillText("YOU WIN!", canvas.width / 2, canvas.height / 2 - 50);
  ctx.fillStyle = "#fff";
  ctx.font = "36px Arial";
  ctx.fillText("All 5 levels completed!", canvas.width / 2, canvas.height / 2 + 20);
  ctx.fillText("Thanks for playing!", canvas.width / 2, canvas.height / 2 + 70);
  ctx.fillText("Press R to play again", canvas.width / 2, canvas.height / 2 + 130);
  ctx.textAlign = "start";
}

function gameLoop() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  if (gameState === "menu") {
    drawMenu();
  } 
  else if (gameState === "playing") {
    if (!gameOver && !levelComplete) {
      updateLevelElements();
      updatePlayer();
      checkCollisions();
    }

    if (levelComplete && finishAnimTimer > 0) {
      finishAnimTimer--;
      if (finishAnimTimer === 0) {
        nextLevel();
      }
    }

    drawGround();
    drawPlatforms();
    drawPlayer();
    drawObstacles();
    drawFinishLine();
    drawHUD();
  }
  else if (gameState === "complete") {
    drawGameComplete();
  }

  requestAnimationFrame(gameLoop);
}

// Input
window.addEventListener("keydown", e => {
  if (gameState === "menu" && e.code === "Enter") {
    startGame();
  }

  if (gameState === "playing" || gameState === "complete") {
    if (e.code === "Space") {
      e.preventDefault();
      player.jumpHeld = true;
      if (player.onGround && !gameOver && !levelComplete) {
        player.vy = jumpVelocity;
        player.onGround = false;
        player.jumping = true;
      }
    }
    if (e.code === "KeyR") {
      hardResetToMenu();
    }
  }
});

window.addEventListener("keyup", e => {
  if (e.code === "Space") player.jumpHeld = false;
});

// Start
hardResetToMenu();
gameLoop();