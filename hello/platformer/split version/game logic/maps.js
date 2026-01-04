function createEmptyMapChars() {
  const arr = [];
  for (let y = 0; y < tilesHigh; y++) {
    const row = [];
    for (let x = 0; x < tilesWide; x++) row.push('.');
    arr.push(row);
  }
  for (let x = 0; x < tilesWide; x++) {
    arr[tilesHigh - 1][x] = '#';
  }
  return arr;
}

function buildDefaultLayout1(chars) {
  const groundY = tilesHigh - 1;

  chars[groundY - 3][10] = '#';
  chars[groundY - 3][11] = '#';

  chars[groundY - 6][15] = '#';
  chars[groundY - 6][16] = '#';
  chars[groundY - 7][15] = 'K';

  chars[groundY - 1][7] = 'J';

  for (let y = groundY - 4; y <= groundY - 1; y++) {
    chars[y][25] = 'L';
  }

  chars[groundY - 1][40] = 'P';

  for (let x = 45; x < 60; x++) {
    chars[groundY][x] = '.';
  }

  chars[groundY - 1][100] = 'P';

  chars[groundY - 4][95] = '#';
  chars[groundY - 4][96] = '#';
  chars[groundY - 6][105] = '#';
  chars[groundY - 6][106] = '#';

  for (let x = 12; x < 18; x++) chars[groundY][x] = 'S';
  chars[groundY - 1][20] = 'T';
}

function buildDefaultLayout2(chars) {
  const groundY = tilesHigh - 1;

  for (let x = 5; x < 20; x++) chars[groundY][x] = '#';
  chars[groundY - 1][8]  = 'J';
  chars[groundY - 5][8]  = '#';
  chars[groundY - 6][8]  = 'J';
  chars[groundY - 10][8] = '#';

  chars[groundY - 11][15] = 'K';
  chars[groundY - 2][30]  = 'L';

  chars[groundY - 12][8]  = 'P';
  chars[groundY - 1][60]  = 'P';

  for (let x = 55; x < 70; x++) chars[groundY - 3][x] = '#';
  for (let x = 80; x < 90; x++) chars[groundY - 8][x] = '#';

  for (let x = 10; x < 14; x++) chars[groundY][x] = 'S';
  chars[groundY - 1][25] = 'T';
}

function makeMap(name, initFn) {
  const mapChars = createEmptyMapChars();
  if (initFn) initFn(mapChars);
  const map = {
    name,
    mapChars,
    platforms: [],
    keys: [],
    locks: [],
    jumpPads: [],
    portals: [],
    spikes: [],
    pistons: [],
    movers: [],
    rotators: []
  };
  rebuildObjectsFromMap(map);
  return map;
}

let maps = [];
let currentMapIndex = 0;

function currentMap() {
  return maps[currentMapIndex];
}

function rebuildObjectsFromMap(mapObj) {
  mapObj.platforms = [];
  mapObj.keys = [];
  mapObj.locks = [];
  mapObj.jumpPads = [];
  mapObj.portals = [];
  mapObj.spikes = [];
  mapObj.pistons = [];
  mapObj.movers   = [];
  mapObj.rotators = [];

  const chars = mapObj.mapChars;

  let keyIdCounter  = 1;
  let lockIdCounter = 1;

  for (let y = 0; y < tilesHigh; y++) {
    for (let x = 0; x < tilesWide; x++) {
      const ch = chars[y][x];
      const wx = x * tileSize;
      const wy = y * tileSize;

      if (ch === '#') {
        mapObj.platforms.push({ x: wx, y: wy, w: tileSize, h: tileSize });
      } else if (ch === 'K') {
        mapObj.keys.push({
          id: keyIdCounter++,
          x: wx, y: wy, w: tileSize, h: tileSize,
          collected: false
        });
      } else if (ch === 'L') {
        mapObj.locks.push({
          id: lockIdCounter++,
          x: wx, y: wy, w: tileSize, h: tileSize,
          open: false
        });
      } else if (ch === 'J') {
        mapObj.jumpPads.push({ x: wx, y: wy, w: tileSize, h: tileSize, power: -22 });
      } else if (ch === 'P') {
        mapObj.portals.push({ x: wx, y: wy, w: tileSize, h: tileSize, targetIndex: -1, cooldown: 0 });
      } else if (ch === 'S') {
        mapObj.spikes.push({ x: wx, y: wy, w: tileSize, h: tileSize });
      } else if (ch === 'T') {
        mapObj.pistons.push({ x: wx, y: wy, w: tileSize, h: tileSize });
      } else if (ch === 'M') {
        mapObj.movers.push({
          originTx: x,
          originTy: y,
          x: wx,
          y: wy,
          w: tileSize,
          h: tileSize,
          pushDist: 100,
          groupTiles: [{ dx: 0, dy: 0, ch: 'M' }],
          phase: 0,
          curX: wx,
          curY: wy,
          prevX: wx,
          prevY: wy
        });
      } else if (ch === 'R') {
        mapObj.rotators.push({
          originTx: x,
          originTy: y,
          x: wx,
          y: wy,
          w: tileSize,
          h: tileSize,
          angle: 0,
          speed: 0.03,
          groupTiles: [{ dx: 0, dy: 0, ch: 'R' }],
          phase: 0,
          curX: wx,
          curY: wy,
          prevX: wx,
          prevY: wy
        });
      }
    }
  }

  if (mapObj.portals.length >= 2) {
    for (let i = 0; i < mapObj.portals.length; i += 2) {
      const j = i + 1;
      if (j < mapObj.portals.length) {
        mapObj.portals[i].targetIndex = j;
        mapObj.portals[j].targetIndex = i;
      }
    }
  }
}

function initMaps() {
  const map0 = makeMap("Start", buildDefaultLayout1);
  const map1 = makeMap("Empty", null);
  const map2 = makeMap("Vertical", buildDefaultLayout2);
  maps = [map0, map1, map2];
  currentMapIndex = 0;
  updateMapLabel();
}

function updateMapLabel() {
  const m = currentMap();
  mapLabel.textContent =
    "Map: " + m.name + " (" + (currentMapIndex + 1) + "/" + maps.length + ")";
}
