// ===== Canvas & constants =====
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

const VIEW_WIDTH = canvas.width;
const VIEW_HEIGHT = canvas.height;

// World bounds for camera clamp
const WORLD_WIDTH  = 2400;   // ~3x view width
const WORLD_HEIGHT = 3000;   // ~5x view height

// Camera
let cameraX = 0;
let cameraY = 0;

// ===== Worlds (10 long, possible maps) =====
const worlds = {
    1: {
  platforms: [
    {x: 0,    y: 2800, w: 2400, h: 40, moving: false},   // ground

    // First jump: only 80px up
    {x: 150,  y: 2720, w: 160,  h: 20, moving: false},

    // Each next step: about 100px up, ≤ 250px over
    {x: 430,  y: 2620, w: 160,  h: 20, moving: false},
    {x: 710,  y: 2520, w: 160,  h: 20, moving: false},
    {x: 990,  y: 2420, w: 160,  h: 20, moving: false},
    {x: 1270, y: 2320, w: 160,  h: 20, moving: false},
    {x: 1550, y: 2220, w: 160,  h: 20, moving: false},
    {x: 1830, y: 2120, w: 160,  h: 20, moving: false},
    {x: 2110, y: 2020, w: 160,  h: 20, moving: false}
  ],
  spikes: [
    {x: 320,  y: 2760, w: 40, h: 40},
    {x: 640,  y: 2760, w: 40, h: 40},
    {x: 960,  y: 2760, w: 40, h: 40}
  ],
  goalX: 2130,
  goalY: 1980   // 2020 - 40
},


    2: { // moving ferries
        platforms: [
            {x: 0,    y: 2800, w: 2400, h: 40, moving: false},
            {x: 150,  y: 2700, w: 140,  h: 20, moving: {dir: 1, speed: 2, minX: 120, maxX: 420}},
            {x: 520,  y: 2580, w: 140,  h: 20, moving: false},
            {x: 820,  y: 2460, w: 140,  h: 20, moving: {dir: -1, speed: 2, minX: 780, maxX: 1100}},
            {x: 1150, y: 2340, w: 140,  h: 20, moving: false},
            {x: 1450, y: 2220, w: 140,  h: 20, moving: {dir: 1, speed: 2, minX: 1400, maxX: 1700}},
            {x: 1780, y: 2100, w: 140,  h: 20, moving: false},
            {x: 2080, y: 1980, w: 160,  h: 20, moving: false}
        ],
        spikes: [
            {x: 300,  y: 2760, w: 40, h: 40},
            {x: 650,  y: 2760, w: 40, h: 40},
            {x: 1000, y: 2760, w: 40, h: 40},
            {x: 1350, y: 2760, w: 40, h: 40}
        ],
        goalX: 2100,
        goalY: 1940          // 1980 - 40
    },

    3: { // S-curve
        platforms: [
            {x: 0,    y: 2800, w: 2400, h: 40, moving: false},
            {x: 200,  y: 2700, w: 160, h: 20, moving: false},
            {x: 520,  y: 2580, w: 160, h: 20, moving: false},
            {x: 840,  y: 2460, w: 160, h: 20, moving: false},
            {x: 1160, y: 2340, w: 160, h: 20, moving: false},
            {x: 1400, y: 2460, w: 160, h: 20, moving: false},
            {x: 1680, y: 2580, w: 160, h: 20, moving: false},
            {x: 1960, y: 2460, w: 160, h: 20, moving: false},
            {x: 2140, y: 2340, w: 160, h: 20, moving: false}
        ],
        spikes: [
            {x: 360,  y: 2760, w: 40, h: 40},
            {x: 720,  y: 2760, w: 40, h: 40},
            {x: 1080, y: 2760, w: 40, h: 40}
        ],
        goalX: 2160,
        goalY: 2300
    },

    4: { // high/low routes
        platforms: [
            {x: 0,    y: 2800, w: 2400, h: 40, moving: false},
            // low
            {x: 200,  y: 2700, w: 120, h: 20, moving: false},
            {x: 500,  y: 2700, w: 120, h: 20, moving: false},
            {x: 800,  y: 2700, w: 120, h: 20, moving: false},
            // high
            {x: 350,  y: 2560, w: 120, h: 20, moving: false},
            {x: 650,  y: 2560, w: 120, h: 20, moving: {dir: 1, speed: 2, minX: 620, maxX: 900}},
            {x: 1000, y: 2560, w: 120, h: 20, moving: false},
            // climb
            {x: 1300, y: 2440, w: 140, h: 20, moving: false},
            {x: 1600, y: 2320, w: 140, h: 20, moving: false},
            {x: 1900, y: 2200, w: 140, h: 20, moving: false},
            {x: 2150, y: 2080, w: 140, h: 20, moving: false}
        ],
        spikes: [
            {x: 320,  y: 2760, w: 40, h: 40},
            {x: 640,  y: 2760, w: 40, h: 40},
            {x: 960,  y: 2760, w: 40, h: 40},
            {x: 1450, y: 2760, w: 40, h: 40}
        ],
        goalX: 2170,
        goalY: 2040
    },

    // Worlds 5–10 can follow same spacing pattern; keep first step around y~2700,
    // and each subsequent platform ~120px higher and ≤250px horizontally away.
    // (You can reuse your previous layouts but lower their y by ~80–100.)
};

// ===== Game state =====
let world = 1;
let lives = 3;
let gameOver = false;

let currentWorld = worlds[world];
let platforms = currentWorld.platforms.slice();
let spikes = currentWorld.spikes.slice();

// Player
const player = {
    x: 100, y: 2720, width: 30, height: 30,
    vx: 0, vy: 0,
    speed: 5,
    jump: -14,
    grounded: false
};

// Input
const keys = {};
window.addEventListener('keydown', e => keys[e.key.toLowerCase()] = true);
window.addEventListener('keyup',   e => keys[e.key.toLowerCase()] = false);

// ===== Helpers =====
function rectCollide(a, b) {
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}

function updatePlayer() {
    player.vx = (keys['arrowleft'] || keys['a']) ? -player.speed :
                (keys['arrowright'] || keys['d']) ?  player.speed :
                                                     player.vx * 0.8;

    if ((keys['arrowup'] || keys['w'] || keys[' ']) && player.grounded) {
        player.vy = player.jump;
        player.grounded = false;
    }

    player.vy += 0.8;

    const oldX = player.x;
    const oldY = player.y;

    player.x += player.vx;
    player.y += player.vy;

    platforms.forEach(p => {
        const plat = { x: p.x, y: p.y, width: p.w, height: p.h };
        if (!rectCollide(player, plat)) return;

        if (oldY + player.height <= p.y) {
            player.y = p.y - player.height;
            player.vy = 0;
            player.grounded = true;
            return;
        }

        const overlapX = Math.min(player.x + player.width - p.x, p.x + p.w - player.x);
        if (overlapX > 10) {
            if (player.vx > 0 && oldX <= p.x) {
                player.x = p.x - player.width;
                player.vx = 0;
            } else if (player.vx < 0 && oldX + player.width >= p.x + p.w) {
                player.x = p.x + p.w;
                player.vx = 0;
            }
        }

        if (oldY >= p.y + p.h) {
            player.y = p.y + p.h;
            player.vy = 0;
        }
    });

    if (player.x < 0) player.x = 0;
    if (player.x > WORLD_WIDTH - player.width) player.x = WORLD_WIDTH - player.width;
    if (player.y > WORLD_HEIGHT) {
        lives--;
        respawn();
    }
}

function updateCamera() {
    cameraX = player.x - VIEW_WIDTH / 2 + player.width / 2;
    cameraY = player.y - VIEW_HEIGHT / 2 + player.height / 2;

    if (cameraX < 0) cameraX = 0;
    if (cameraY < 0) cameraY = 0;
    if (cameraX > WORLD_WIDTH - VIEW_WIDTH) cameraX = WORLD_WIDTH - VIEW_WIDTH;
    if (cameraY > WORLD_HEIGHT - VIEW_HEIGHT) cameraY = WORLD_HEIGHT - VIEW_HEIGHT;
}

function respawn() {
    player.x = 100;
    player.y = 2720;        // just above ground, near first step
    player.vx = 0;
    player.vy = 0;
    player.grounded = false;
    if (lives <= 0) gameOver = true;
}

// ===== Main loop =====
function gameLoop() {
    ctx.clearRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);

    platforms.forEach(p => {
        if (p.moving) {
            p.x += p.moving.dir * p.moving.speed;
            if (p.x <= p.moving.minX) p.moving.dir = 1;
            else if (p.x + p.w >= p.moving.maxX) p.moving.dir = -1;
        }
    });

    if (!gameOver) {
        updatePlayer();
        updateCamera();

        spikes.forEach(s => {
            const box = { x: s.x, y: s.y, width: s.w, height: s.h };
            if (rectCollide(player, box)) {
                lives--;
                respawn();
            }
        });

        // goal is 40×40
        const goalBox = {
            x: currentWorld.goalX,
            y: currentWorld.goalY,
            width: 40,
            height: 40
        };
        if (rectCollide(player, goalBox)) {
            world++;
            if (worlds[world]) {
                currentWorld = worlds[world];
                platforms = currentWorld.platforms.slice();
                spikes = currentWorld.spikes.slice();
                respawn();
            } else {
                alert('You beat all worlds!');
                location.reload();
                return;
            }
        }
    }

    // Grid background
    ctx.shadowBlur = 20;
    ctx.fillStyle = 'rgba(0,255,204,0.05)';
    for (let i = 0; i < VIEW_WIDTH; i += 40) {
        ctx.fillRect(i, 0, 2, VIEW_HEIGHT);
    }
    for (let j = 0; j < VIEW_HEIGHT; j += 40) {
        ctx.fillRect(0, j, VIEW_WIDTH, 2);
    }

    // Platforms
    ctx.shadowColor = '#ff00ff';
    ctx.shadowBlur = 20;
    ctx.fillStyle = '#ff00ff';
    platforms.forEach(p => {
        ctx.fillRect(p.x - cameraX, p.y - cameraY, p.w, p.h);
    });
    ctx.shadowBlur = 0;
    ctx.strokeStyle = '#ff44ff';
    ctx.lineWidth = 2;
    platforms.forEach(p => {
        ctx.strokeRect(p.x - cameraX, p.y - cameraY, p.w, p.h);
    });

    // Spikes
    ctx.shadowColor = '#ff4444';
    ctx.shadowBlur = 15;
    ctx.fillStyle = '#ff4444';
    spikes.forEach(s => {
        ctx.beginPath();
        ctx.moveTo(s.x + 20 - cameraX, s.y - cameraY);
        ctx.lineTo(s.x - cameraX,       s.y + 40 - cameraY);
        ctx.lineTo(s.x + 40 - cameraX,  s.y + 40 - cameraY);
        ctx.fill();
    });

    // Goal
    ctx.shadowColor = '#44ff44';
    ctx.shadowBlur = 20;
    ctx.fillStyle = '#44ff44';
    ctx.fillRect(currentWorld.goalX - cameraX, currentWorld.goalY - cameraY, 40, 40);

    // Player
    ctx.shadowColor = '#00ffcc';
    ctx.shadowBlur = 25;
    ctx.fillStyle = '#00ffcc';
    ctx.fillRect(player.x - cameraX, player.y - cameraY, player.width, player.height);
    ctx.shadowBlur = 0;
    ctx.strokeStyle = '#ffffff';
    ctx.lineWidth = 2;
    ctx.strokeRect(player.x - cameraX, player.y - cameraY, player.width, player.height);

    document.getElementById('world').textContent = world;
    document.getElementById('lives').textContent = lives;

    requestAnimationFrame(gameLoop);
}

gameLoop();
