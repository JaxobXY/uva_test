// Canvas and context
const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');

// UI elements
const playBtn    = document.getElementById('playBtn');
const editorBtn  = document.getElementById('editorBtn');
const clearBtn   = document.getElementById('clearBtn');
const editorUI   = document.getElementById('editorUI');
const editorInfo = document.getElementById('editorInfo');

const prevMapBtn = document.getElementById('prevMapBtn');
const nextMapBtn = document.getElementById('nextMapBtn');
const mapLabel   = document.getElementById('mapLabel');

const upBtn      = document.getElementById('upBtn');
const leftBtn    = document.getElementById('leftBtn');
const downBtn    = document.getElementById('downBtn');
const rightBtn   = document.getElementById('rightBtn');
const zoomInBtn  = document.getElementById('zoomInBtn');
const zoomOutBtn = document.getElementById('zoomOutBtn');

const hotbar     = document.getElementById('hotbar');
const hotButtons = hotbar.querySelectorAll('.hotBtn');

// Game/editor mode
let mode = "game";

// Input state
const input = { left: false, right: false, jump: false, down: false };

// Camera
let cameraX = 0;
let cameraY = 0;
let cameraZoom = 1;
const minZoom = 0.5;
const maxZoom = 2.5;

// Editor tile state
let currentTileType = '#';

let activeMover   = null;
let activeRotator = null;
let gluePlacement = false;

// World size
const tileSize   = 25;
const tilesWide  = 128; 
const tilesHigh  = 72;
const levelWidth  = tilesWide * tileSize;
const levelHeight = tilesHigh * tileSize;
