import React, { useState, useEffect, useRef, useCallback } from 'react';

const Game = () => {
  const canvasRef = useRef(null);
  const animationRef = useRef(null);
  
  // Game modes and track selection
  const [gameMode, setGameMode] = useState('menu');
  const [selectedTrack, setSelectedTrack] = useState('plains');
  const [isPlayer1Turn, setIsPlayer1Turn] = useState(true);
  const [customMaps, setCustomMaps] = useState([]);
  const [designingMap, setDesigningMap] = useState(null);
  const [drawingPath, setDrawingPath] = useState(false);
  
  // Game state
  const [gameState, setGameState] = useState({
    lives: 100,
    money: 650,
    wave: 1,
    score: 0,
    gameSpeed: 1,
    isPaused: false,
    isGameOver: false,
    player1: { lives: 150, money: 650, score: 0 },
    player2: { lives: 150, money: 650, score: 0 }
  });
  
  const [selectedTower, setSelectedTower] = useState(null);
  const [placingTower, setPlacingTower] = useState(null);
  const [towers, setTowers] = useState([]);
  const [balloons, setBalloons] = useState([]);
  const [projectiles, setProjectiles] = useState([]);
  const [explosions, setExplosions] = useState([]);
  const [waveInProgress, setWaveInProgress] = useState(false);
  const [waveCompleted, setWaveCompleted] = useState(false);
  
  // Game dimensions
  const CANVAS_WIDTH = 800;
  const CANVAS_HEIGHT = 600;
  
  // Track definitions
  const TRACKS = {
    plains: {
      name: 'Grasslands',
      background: '#90EE90',
      pathColor: '#8B4513',
      pathBorder: '#654321',
      path: [
        {x: 0, y: 300}, {x: 150, y: 300}, {x: 150, y: 200},
        {x: 300, y: 200}, {x: 300, y: 400}, {x: 450, y: 400},
        {x: 450, y: 150}, {x: 600, y: 150}, {x: 600, y: 450},
        {x: 750, y: 450}, {x: 750, y: 300}, {x: 800, y: 300}
      ]
    },
    desert: {
      name: 'Sandy Dunes',
      background: '#F4A460',
      pathColor: '#D2691E',
      pathBorder: '#8B4513',
      path: [
        {x: 0, y: 200}, {x: 200, y: 200}, {x: 200, y: 400},
        {x: 400, y: 400}, {x: 400, y: 100}, {x: 600, y: 100},
        {x: 600, y: 500}, {x: 800, y: 500}
      ]
    },
    snowy: {
      name: 'Frozen Peaks',
      background: '#F0F8FF',
      pathColor: '#C0C0C0',
      pathBorder: '#696969',
      path: [
        {x: 0, y: 350}, {x: 100, y: 350}, {x: 100, y: 150},
        {x: 250, y: 150}, {x: 250, y: 450}, {x: 400, y: 450},
        {x: 400, y: 100}, {x: 550, y: 100}, {x: 550, y: 400},
        {x: 700, y: 400}, {x: 700, y: 250}, {x: 800, y: 250}
      ]
    },
    mountain: {
      name: 'Rocky Heights',
      background: '#A0522D',
      pathColor: '#696969',
      pathBorder: '#2F4F4F',
      path: [
        {x: 0, y: 250}, {x: 120, y: 250}, {x: 120, y: 450},
        {x: 280, y: 450}, {x: 280, y: 180}, {x: 520, y: 180},
        {x: 520, y: 420}, {x: 680, y: 420}, {x: 680, y: 300},
        {x: 800, y: 300}
      ]
    },
    volcano: {
      name: 'Volcanic Crater',
      background: '#FF4500',
      pathColor: '#8B0000',
      pathBorder: '#FF6347',
      path: [
        {x: 0, y: 300}, {x: 100, y: 300}, {x: 150, y: 200},
        {x: 200, y: 100}, {x: 300, y: 80}, {x: 400, y: 100},
        {x: 500, y: 200}, {x: 600, y: 300}, {x: 650, y: 400},
        {x: 700, y: 500}, {x: 800, y: 520}
      ]
    },
    ocean: {
      name: 'Coral Reef',
      background: '#00CED1',
      pathColor: '#4682B4',
      pathBorder: '#191970',
      path: [
        {x: 0, y: 400}, {x: 80, y: 350}, {x: 160, y: 300},
        {x: 240, y: 250}, {x: 320, y: 200}, {x: 400, y: 150},
        {x: 480, y: 200}, {x: 560, y: 250}, {x: 640, y: 300},
        {x: 720, y: 350}, {x: 800, y: 400}
      ]
    },
    jungle: {
      name: 'Dense Jungle',
      background: '#228B22',
      pathColor: '#654321',
      pathBorder: '#8B4513',
      path: [
        {x: 0, y: 100}, {x: 100, y: 150}, {x: 200, y: 200},
        {x: 300, y: 300}, {x: 400, y: 400}, {x: 500, y: 500},
        {x: 600, y: 450}, {x: 700, y: 350}, {x: 800, y: 250}
      ]
    },
    city: {
      name: 'Urban Skyline',
      background: '#708090',
      pathColor: '#2F4F4F',
      pathBorder: '#000000',
      path: [
        {x: 0, y: 500}, {x: 150, y: 500}, {x: 150, y: 300},
        {x: 300, y: 300}, {x: 300, y: 100}, {x: 450, y: 100},
        {x: 450, y: 350}, {x: 600, y: 350}, {x: 600, y: 200},
        {x: 750, y: 200}, {x: 750, y: 50}, {x: 800, y: 50}
      ]
    }
  };
  
  // Add custom maps to tracks
  const getAllTracks = () => {
    const allTracks = { ...TRACKS };
    customMaps.forEach((map, index) => {
      allTracks[`custom_${index}`] = map;
    });
    return allTracks;
  };
  
  const PATH = getAllTracks()[selectedTrack]?.path || TRACKS.plains.path;
  
  // Calculate path distances for consistent speed
  const getPathDistances = () => {
    const distances = [0];
    let totalDistance = 0;
    
    for (let i = 1; i < PATH.length; i++) {
      const dx = PATH[i].x - PATH[i-1].x;
      const dy = PATH[i].y - PATH[i-1].y;
      const segmentDistance = Math.sqrt(dx * dx + dy * dy);
      totalDistance += segmentDistance;
      distances.push(totalDistance);
    }
    
    return { distances, totalDistance };
  };
  
  const pathData = getPathDistances();
  
  // Tower definitions - Complete set from first code
  const TOWER_TYPES = {
    dart: {
      name: 'Dart Monkey',
      cost: 170,
      damage: 1,
      range: 80,
      fireRate: 1.2,
      projectileSpeed: 8,
      color: '#8B4513',
      projectileCount: 1,
      upgrades: {
        path1: ['Sharp Shots', 'Razor Sharp Shots', 'Spike-O-Pult'],
        path2: ['Long Range Darts', 'Enhanced Eyesight', 'Super Monkey Fan Club'],
        path3: ['Quick Shots', 'Very Quick Shots', 'Triple Shot']
      }
    },
    tack: {
      name: 'Tack Shooter',
      cost: 280,
      damage: 1,
      range: 60,
      fireRate: 1.5,
      projectileSpeed: 6,
      color: '#FF6B35',
      projectileCount: 8,
      spreadAngle: 360,
      upgrades: {
        path1: ['Faster Shooting', 'Even Faster Shooting', 'Tack Sprayer'],
        path2: ['Long Range Tacks', 'Super Long Range Tacks', 'Blade Shooter'],
        path3: ['More Tacks', 'Even More Tacks', 'Ring of Fire']
      }
    },
    sniper: {
      name: 'Sniper Monkey',
      cost: 350,
      damage: 2,
      range: 999,
      fireRate: 0.6,
      projectileSpeed: 15,
      color: '#2D5016',
      projectileCount: 1,
      upgrades: {
        path1: ['Full Metal Jacket', 'Large Calibre', 'Deadly Precision'],
        path2: ['Night Vision Goggles', 'Semi-Automatic Rifle', 'Supply Drop'],
        path3: ['Fast Firing', 'Even Faster Firing', 'Cripple MOAB']
      }
    },
    bomb: {
      name: 'Bomb Shooter',
      cost: 525,
      damage: 1,
      range: 70,
      fireRate: 0.8,
      projectileSpeed: 5,
      color: '#4A4A4A',
      explosionRadius: 30,
      projectileCount: 1,
      upgrades: {
        path1: ['Bigger Bombs', 'Really Big Bombs', 'MOAB Mauler'],
        path2: ['Frag Bombs', 'Cluster Bombs', 'MOAB Assassin'],
        path3: ['Faster Reload', 'Missile Launcher', 'MOAB Eliminator']
      }
    },
    ice: {
      name: 'Ice Monkey',
      cost: 425,
      damage: 0,
      range: 65,
      fireRate: 2.0,
      projectileSpeed: 0,
      color: '#87CEEB',
      slowAmount: 0.5,
      slowDuration: 3000,
      upgrades: {
        path1: ['Enhanced Freeze', 'Ice Shards', 'Arctic Wind'],
        path2: ['Permafrost', 'Deep Freeze', 'Absolute Zero'],
        path3: ['Snap Freeze', 'Viral Frost', 'Icicle Impale']
      }
    },
    super: {
      name: 'Super Monkey',
      cost: 2500,
      damage: 1,
      range: 80,
      fireRate: 15,
      projectileSpeed: 12,
      color: '#FFD700',
      projectileCount: 2,
      spreadAngle: 10,
      upgrades: {
        path1: ['Laser Blasts', 'Plasma Blasts', 'Sun God'],
        path2: ['Super Range', 'Epic Range', 'Robo Monkey'],
        path3: ['Knockback', 'Hydra Rocket Pods', 'Technological Terror']
      }
    },
    ninja: {
      name: 'Ninja Monkey',
      cost: 500,
      damage: 1,
      range: 75,
      fireRate: 2.5,
      projectileSpeed: 10,
      color: '#2C2C54',
      projectileCount: 2,
      spreadAngle: 15,
      upgrades: {
        path1: ['Ninja Discipline', 'Sharp Shurikens', 'Double Shot'],
        path2: ['Bloon Sabotage', 'Counter-Espionage', 'Grand Saboteur'],
        path3: ['Seeking Shuriken', 'Caltrops', 'Flash Bomb']
      }
    },
    boomerang: {
      name: 'Boomerang Monkey',
      cost: 325,
      damage: 1,
      range: 85,
      fireRate: 1.8,
      projectileSpeed: 7,
      color: '#8B4513',
      canHitMultiple: true,
      projectileCount: 1,
      upgrades: {
        path1: ['Multi-Target', 'Glaive Ricochet', 'Glaive Lord'],
        path2: ['Sonic Boom', 'Red Hot Rangs', 'Turbo Charge'],
        path3: ['Bionic Boomerang', 'Turbo Charge', 'Perma Charge']
      }
    },
    wizard: {
      name: 'Wizard Monkey',
      cost: 375,
      damage: 1,
      range: 70,
      fireRate: 1.4,
      projectileSpeed: 8,
      color: '#4B0082',
      projectileCount: 1,
      upgrades: {
        path1: ['Guided Magic', 'Fireball', 'Phoenix'],
        path2: ['Monkey Sense', 'Shimmer', 'Summon Phoenix'],
        path3: ['Intense Magic', 'Monkey Apprentice', 'Arcane Mastery']
      }
    },
    glue: {
      name: 'Glue Gunner',
      cost: 275,
      damage: 0,
      range: 65,
      fireRate: 1.1,
      projectileSpeed: 6,
      color: '#DAA520',
      slowAmount: 0.3,
      slowDuration: 4000,
      upgrades: {
        path1: ['Stickier Glue', 'Stronger Glue', 'MOAB Glue'],
        path2: ['Corrosive Glue', 'Relentless Glue', 'Super Glue'],
        path3: ['Bloon Dissolver', 'Glue Strike', 'Glue Storm']
      }
    },
    engineer: {
      name: 'Engineer Monkey',
      cost: 440,
      damage: 1,
      range: 75,
      fireRate: 1.6,
      projectileSpeed: 9,
      color: '#B8860B',
      projectileCount: 1,
      upgrades: {
        path1: ['Larger Service Area', 'Sprockets', 'Overclock'],
        path2: ['Sentries', 'Faster Engineering', 'Sentry Expert'],
        path3: ['Nail Gun', 'Bigger Nails', 'XXXL Trap']
      }
    },
    mortar: {
      name: 'Mortar Monkey',
      cost: 750,
      damage: 1,
      range: 999,
      fireRate: 0.7,
      projectileSpeed: 12,
      color: '#696969',
      explosionRadius: 45,
      upgrades: {
        path1: ['Bigger Blast', 'Bloon Buster', 'Shell Shock'],
        path2: ['Rapid Reload', 'Heavy Shells', 'Artillery Battery'],
        path3: ['Burny Stuff', 'Signal Flare', 'Pop & Awe']
      }
    }
  };
  
  // Balloon definitions - Complete set including MOAB variants and special types
  const BALLOON_TYPES = {
    red: { health: 1, speed: 1, cost: 1, reward: 1, color: '#FF0000', children: [] },
    blue: { health: 2, speed: 1.4, cost: 2, reward: 2, color: '#0066FF', children: ['red'] },
    green: { health: 3, speed: 1.8, cost: 3, reward: 3, color: '#00AA00', children: ['blue'] },
    yellow: { health: 4, speed: 3.2, cost: 4, reward: 4, color: '#FFFF00', children: ['green'] },
    pink: { health: 5, speed: 3.5, cost: 5, reward: 5, color: '#FFB6C1', children: ['yellow'] },
    black: { health: 11, speed: 1.8, cost: 11, reward: 11, color: '#000000', children: ['pink', 'pink'], immuneTo: ['explosion'] },
    white: { health: 11, speed: 2.0, cost: 11, reward: 11, color: '#FFFFFF', children: ['pink', 'pink'], immuneTo: ['freeze'] },
    lead: { health: 23, speed: 1.0, cost: 23, reward: 23, color: '#808080', children: ['black', 'black'], immuneTo: ['sharp'] },
    zebra: { health: 23, speed: 1.8, cost: 23, reward: 23, color: '#000000', children: ['black', 'white'], immuneTo: ['explosion', 'freeze'] },
    rainbow: { health: 47, speed: 2.2, cost: 47, reward: 47, color: '#FF69B4', children: ['zebra', 'zebra'] },
    ceramic: { health: 104, speed: 2.0, cost: 104, reward: 104, color: '#8B4513', children: ['rainbow', 'rainbow'] },
    // MOAB Class Balloons
    moab: { health: 200, speed: 1.0, cost: 200, reward: 200, color: '#4169E1', children: ['ceramic', 'ceramic', 'ceramic', 'ceramic'], isMoab: true },
    bfb: { health: 700, speed: 0.25, cost: 700, reward: 700, color: '#FF1493', children: ['moab', 'moab', 'moab', 'moab'], isMoab: true, immuneTo: ['sharp'] },
    zomg: { health: 4000, speed: 0.18, cost: 4000, reward: 4000, color: '#32CD32', children: ['bfb', 'bfb', 'bfb', 'bfb'], isMoab: true, immuneTo: ['sharp', 'explosion'] },
    bad: { health: 20000, speed: 0.18, cost: 20000, reward: 20000, color: '#8B0000', children: ['zomg', 'zomg'], isMoab: true, immuneTo: ['sharp', 'explosion', 'freeze'] },
    ddt: { health: 400, speed: 2.75, cost: 400, reward: 400, color: '#2F4F4F', children: ['ceramic', 'ceramic', 'ceramic', 'ceramic', 'ceramic', 'ceramic'], isMoab: true, immuneTo: ['sharp', 'explosion'], camo: true },
    // Special Balloons
    purple: { health: 11, speed: 2.2, cost: 15, reward: 15, color: '#800080', children: ['pink', 'pink'], immuneTo: ['magic'] },
    fortified_red: { health: 2, speed: 1, cost: 3, reward: 3, color: '#FF0000', children: ['red'], fortified: true },
    fortified_ceramic: { health: 208, speed: 2.0, cost: 208, reward: 208, color: '#654321', children: ['rainbow', 'rainbow'], fortified: true },
    camo_green: { health: 3, speed: 1.8, cost: 5, reward: 5, color: '#228B22', children: ['blue'], camo: true },
    camo_lead: { health: 23, speed: 1.0, cost: 35, reward: 35, color: '#696969', children: ['black', 'black'], immuneTo: ['sharp'], camo: true },
    regrow_blue: { health: 2, speed: 1.4, cost: 4, reward: 4, color: '#4169E1', children: ['red'], regrow: true },
    regrow_ceramic: { health: 104, speed: 2.0, cost: 150, reward: 150, color: '#A0522D', children: ['rainbow', 'rainbow'], regrow: true }
  };
  
  // Wave definitions - Enhanced with new balloon types
  const getWaveData = (wave) => {
    const baseWaves = [
      [{ type: 'red', count: 20, spacing: 500 }],
      [{ type: 'red', count: 35, spacing: 400 }],
      [{ type: 'red', count: 25, spacing: 300 }, { type: 'blue', count: 15, spacing: 400 }],
      [{ type: 'blue', count: 30, spacing: 350 }],
      [{ type: 'red', count: 20, spacing: 200 }, { type: 'green', count: 20, spacing: 300 }],
      [{ type: 'yellow', count: 25, spacing: 250 }],
      [{ type: 'green', count: 30, spacing: 200 }],
      [{ type: 'pink', count: 20, spacing: 300 }],
      [{ type: 'yellow', count: 20, spacing: 200 }, { type: 'pink', count: 10, spacing: 400 }],
      [{ type: 'rainbow', count: 15, spacing: 500 }],
      [{ type: 'black', count: 10, spacing: 600 }, { type: 'white', count: 10, spacing: 600 }],
      [{ type: 'lead', count: 8, spacing: 800 }],
      [{ type: 'zebra', count: 12, spacing: 600 }],
      [{ type: 'rainbow', count: 20, spacing: 400 }],
      [{ type: 'ceramic', count: 8, spacing: 800 }],
      [{ type: 'purple', count: 15, spacing: 500 }, { type: 'lead', count: 5, spacing: 1000 }],
      [{ type: 'fortified_ceramic', count: 6, spacing: 1000 }],
      [{ type: 'camo_lead', count: 10, spacing: 600 }],
      [{ type: 'regrow_ceramic', count: 5, spacing: 1200 }],
      [{ type: 'moab', count: 1, spacing: 0 }],
      [{ type: 'ceramic', count: 15, spacing: 400 }, { type: 'moab', count: 2, spacing: 5000 }],
      [{ type: 'fortified_ceramic', count: 10, spacing: 600 }, { type: 'moab', count: 1, spacing: 3000 }],
      [{ type: 'ddt', count: 1, spacing: 0 }],
      [{ type: 'moab', count: 3, spacing: 3000 }],
      [{ type: 'bfb', count: 1, spacing: 0 }],
      [{ type: 'ddt', count: 2, spacing: 4000 }, { type: 'moab', count: 2, spacing: 2000 }],
      [{ type: 'fortified_ceramic', count: 20, spacing: 300 }, { type: 'bfb', count: 1, spacing: 8000 }],
      [{ type: 'moab', count: 5, spacing: 2000 }],
      [{ type: 'bfb', count: 2, spacing: 6000 }],
      [{ type: 'zomg', count: 1, spacing: 0 }],
      [{ type: 'ddt', count: 4, spacing: 2000 }, { type: 'bfb', count: 1, spacing: 5000 }],
      [{ type: 'zomg', count: 1, spacing: 0 }, { type: 'bfb', count: 2, spacing: 4000 }],
      [{ type: 'fortified_ceramic', count: 30, spacing: 200 }, { type: 'zomg', count: 1, spacing: 10000 }],
      [{ type: 'moab', count: 8, spacing: 1500 }],
      [{ type: 'bfb', count: 3, spacing: 4000 }],
      [{ type: 'zomg', count: 2, spacing: 8000 }],
      [{ type: 'ddt', count: 6, spacing: 1500 }, { type: 'zomg', count: 1, spacing: 6000 }],
      [{ type: 'bad', count: 1, spacing: 0 }],
      [{ type: 'zomg', count: 3, spacing: 5000 }, { type: 'bad', count: 1, spacing: 15000 }],
      [{ type: 'bad', count: 2, spacing: 10000 }]
    ];
    
    if (wave <= baseWaves.length) {
      return baseWaves[wave - 1];
    }
    
    // Post-wave 40: Escalating difficulty with mixed MOAB types
    const postGameTypes = ['bad', 'zomg', 'bfb', 'ddt', 'fortified_ceramic'];
    const waveMultiplier = Math.floor((wave - 40) / 10) + 1;
    
    return [
      { 
        type: postGameTypes[wave % postGameTypes.length], 
        count: Math.min(1 + Math.floor(wave / 20), 5) * waveMultiplier, 
        spacing: Math.max(2000, 8000 - wave * 50) 
      },
      {
        type: 'fortified_ceramic',
        count: Math.min(10 + wave, 50),
        spacing: Math.max(100, 300 - wave * 2)
      }
    ];
  };
  
  // Utility functions
  const distance = (a, b) => Math.sqrt((a.x - b.x) ** 2 + (a.y - b.y) ** 2);
  
  const getPathPosition = (progress) => {
    if (progress <= 0) return PATH[0];
    if (progress >= 1) return PATH[PATH.length - 1];
    
    // Convert progress (0-1) to distance along path
    const targetDistance = progress * pathData.totalDistance;
    
    // Find which segment we're on
    let segmentIndex = 0;
    for (let i = 1; i < pathData.distances.length; i++) {
      if (targetDistance <= pathData.distances[i]) {
        segmentIndex = i - 1;
        break;
      }
    }
    
    if (segmentIndex >= PATH.length - 1) return PATH[PATH.length - 1];
    
    // Calculate position within the segment
    const segmentStart = pathData.distances[segmentIndex];
    const segmentEnd = pathData.distances[segmentIndex + 1];
    const segmentProgress = (targetDistance - segmentStart) / (segmentEnd - segmentStart);
    
    const start = PATH[segmentIndex];
    const end = PATH[segmentIndex + 1];
    
    return {
      x: start.x + (end.x - start.x) * segmentProgress,
      y: start.y + (end.y - start.y) * segmentProgress
    };
  };
  
  const spawnWave = useCallback(() => {
    if (waveInProgress || gameMode !== 'singleplayer') return;
    
    setWaveInProgress(true);
    setWaveCompleted(false);
    const waveData = getWaveData(gameState.wave);
    let totalDelay = 0;
    
    waveData.forEach((group) => {
      for (let i = 0; i < group.count; i++) {
        setTimeout(() => {
          setBalloons(prev => [...prev, {
            id: Date.now() + Math.random(),
            type: group.type,
            ...BALLOON_TYPES[group.type],
            progress: -0.05 - i * 0.02,
            iceSlowed: false,
            iceSlowEndTime: 0,
            glued: false,
            glueEndTime: 0,
            corrosive: false,
            corrosiveEndTime: 0,
            sentByPlayer: 0
          }]);
        }, totalDelay + i * group.spacing);
      }
      totalDelay += group.count * group.spacing + 1000;
    });
    
    setTimeout(() => {
      setWaveInProgress(false);
      setWaveCompleted(true);
    }, totalDelay);
  }, [gameState.wave, waveInProgress, gameMode]);
  
  const placeTower = (x, y, type) => {
    const towerData = TOWER_TYPES[type];
    const currentMoney = gameMode === 'sandbox' ? 999999 : // Infinite money in sandbox
      gameMode === 'multiplayer' ? 
        (isPlayer1Turn ? gameState.player1.money : gameState.player2.money) : gameState.money;
    
    if (currentMoney >= towerData.cost) {
      const newTower = {
        id: Date.now(),
        type,
        x,
        y,
        ...towerData,
        lastFired: 0,
        upgradeLevel: { path1: 0, path2: 0, path3: 0 },
        selectedPath: null,
        owner: gameMode === 'multiplayer' ? (isPlayer1Turn ? 1 : 2) : 0
      };
      
      setTowers(prev => [...prev, newTower]);
      
      if (gameMode === 'multiplayer') {
        const playerKey = isPlayer1Turn ? 'player1' : 'player2';
        setGameState(prev => ({
          ...prev,
          [playerKey]: {
            ...prev[playerKey],
            money: prev[playerKey].money - towerData.cost
          }
        }));
        setIsPlayer1Turn(!isPlayer1Turn);
      } else if (gameMode === 'singleplayer') {
        setGameState(prev => ({ ...prev, money: prev.money - towerData.cost }));
      }
      // In sandbox mode, don't deduct money
      
      setPlacingTower(null);
    }
  };
  
  const sellTower = (towerId) => {
    const tower = towers.find(t => t.id === towerId);
    if (tower) {
      const baseValue = Math.floor(tower.cost * 0.7);
      const upgradeValue = Object.values(tower.upgradeLevel).reduce((sum, level) => {
        return sum + (level * 100 + (level * (level - 1) / 2) * 150) * 0.7;
      }, 0);
      const sellValue = Math.floor(baseValue + upgradeValue);
      
      setTowers(prev => prev.filter(t => t.id !== towerId));
      
      if (gameMode === 'multiplayer') {
        const playerKey = tower.owner === 1 ? 'player1' : 'player2';
        setGameState(prev => ({
          ...prev,
          [playerKey]: {
            ...prev[playerKey],
            money: prev[playerKey].money + sellValue
          }
        }));
      } else if (gameMode === 'singleplayer') {
        setGameState(prev => ({ ...prev, money: prev.money + sellValue }));
      }
      // In sandbox mode, don't need to give money back since it's infinite
      setSelectedTower(null);
    }
  };

  const upgradeTower = (towerId, path) => {
    setTowers(prev => prev.map(tower => {
      if (tower.id === towerId) {
        const currentLevel = tower.upgradeLevel[path];
        if (currentLevel < 3) {
          const upgradeCost = 100 + currentLevel * 150;
          const currentMoney = gameMode === 'sandbox' ? 999999 : // Infinite money in sandbox
            gameMode === 'multiplayer' ? 
              (tower.owner === 1 ? gameState.player1.money : gameState.player2.money) : gameState.money;
          
          if (currentMoney >= upgradeCost) {
            if (gameMode === 'multiplayer') {
              const playerKey = tower.owner === 1 ? 'player1' : 'player2';
              setGameState(prev => ({
                ...prev,
                [playerKey]: {
                  ...prev[playerKey],
                  money: prev[playerKey].money - upgradeCost
                }
              }));
            } else if (gameMode === 'singleplayer') {
              setGameState(prev => ({ ...prev, money: prev.money - upgradeCost }));
            }
            // In sandbox mode, don't deduct money
            
            const newUpgradeLevel = { ...tower.upgradeLevel, [path]: currentLevel + 1 };
            let newProjectileCount = tower.projectileCount;
            
            // Handle specific upgrade effects
            if (tower.type === 'dart' && path === 'path3' && newUpgradeLevel.path3 === 3) {
              newProjectileCount = 3; // Triple Shot upgrade
            }
            if (tower.type === 'tack' && path === 'path3') {
              newProjectileCount = tower.projectileCount + newUpgradeLevel.path3 * 2; // More Tacks upgrades
            }
            if (tower.type === 'ninja' && path === 'path1' && newUpgradeLevel.path1 === 3) {
              newProjectileCount = 4; // Double Shot upgrade
            }
            if (tower.type === 'super' && path === 'path3' && newUpgradeLevel.path3 >= 1) {
              newProjectileCount = 2 + newUpgradeLevel.path3; // More projectiles with upgrades
            }
            
            return {
              ...tower,
              upgradeLevel: newUpgradeLevel,
              selectedPath: tower.selectedPath || path,
              damage: tower.damage + (path === 'path1' ? 1 : 0),
              range: tower.range + (path === 'path2' ? 20 : 0),
              fireRate: tower.fireRate * (path === 'path3' ? 1.3 : 1),
              projectileCount: newProjectileCount,
              // Update slow amounts and durations for ice/glue towers
              slowAmount: tower.type === 'ice' && path === 'path3' && newUpgradeLevel.path3 >= 1 ? 0.3 : tower.slowAmount,
              slowDuration: tower.type === 'glue' && path === 'path1' && newUpgradeLevel.path1 >= 2 ? 6000 : tower.slowDuration
            };
          }
        }
      }
      return tower;
    }));
  };
  
  // Game loop with complete tower firing logic
  const gameLoop = useCallback(() => {
    if (gameState.isPaused || gameState.isGameOver) return;
    
    const currentTime = Date.now();
    
    // Update balloons
    setBalloons(prev => {
      const updated = prev.map(balloon => {
        // Check if ice slow effect should wear off
        if (balloon.iceSlowed && currentTime > balloon.iceSlowEndTime) {
          return { ...balloon, iceSlowed: false, iceSlowEndTime: 0 };
        }
        
        // Check if glue effect should wear off
        if (balloon.glued && currentTime > balloon.glueEndTime) {
          return { ...balloon, glued: false, glueEndTime: 0 };
        }
        
        // Check if corrosive effect should wear off
        if (balloon.corrosive && currentTime > balloon.corrosiveEndTime) {
          return { ...balloon, corrosive: false, corrosiveEndTime: 0, lastCorrosiveDamage: 0 };
        }
        
        // Apply corrosive damage over time
        if (balloon.corrosive && currentTime - (balloon.lastCorrosiveDamage || 0) > 500) {
          const newHealth = balloon.health - 1;
          if (newHealth <= 0) {
            // Balloon destroyed by corrosion
            const reward = BALLOON_TYPES[balloon.type].reward;
            
            if (gameMode === 'multiplayer') {
              const playerKey = balloon.sentByPlayer === 1 ? 'player2' : 'player1';
              setGameState(prev => ({
                ...prev,
                [playerKey]: {
                  ...prev[playerKey],
                  money: prev[playerKey].money + reward,
                  score: prev[playerKey].score + reward
                }
              }));
            } else {
              setGameState(prev => ({
                ...prev,
                money: prev.money + reward,
                score: prev.score + reward
              }));
            }
            
            // Spawn children
            if (balloon.children && balloon.children.length > 0) {
              setTimeout(() => {
                const childBalloons = balloon.children.map(childType => ({
                  id: Date.now() + Math.random(),
                  type: childType,
                  ...BALLOON_TYPES[childType],
                  progress: balloon.progress,
                  iceSlowed: false,
                  iceSlowEndTime: 0,
                  glued: false,
                  glueEndTime: 0,
                  sentByPlayer: balloon.sentByPlayer
                }));
                setBalloons(prev => [...prev, ...childBalloons]);
              }, 50);
            }
            
            return null; // Remove balloon
          }
          
          return {
            ...balloon,
            health: newHealth,
            lastCorrosiveDamage: currentTime
          };
        }
        
        // Calculate speed multipliers
        let speedMultiplier = 1;
        
        if (balloon.iceSlowed) {
          speedMultiplier *= balloon.iceSlowAmount || 0.5; // Default 50% speed when ice slowed
        }
        
        if (balloon.glued) {
          speedMultiplier *= balloon.glueSlowAmount || 0.3; // Default 30% speed when glued
        }
        
        const speedPerFrame = (balloon.speed * speedMultiplier * 0.0008 * gameState.gameSpeed);
        return {
          ...balloon,
          progress: balloon.progress + speedPerFrame
        };
      }).filter(balloon => {
        if (balloon === null) return false; // Remove balloons destroyed by corrosion
        
        if (balloon.progress >= 1) {
          if (gameMode === 'multiplayer') {
            const defendingPlayer = balloon.sentByPlayer === 1 ? 'player2' : 'player1';
            setGameState(prev => ({
              ...prev,
              [defendingPlayer]: {
                ...prev[defendingPlayer],
                lives: prev[defendingPlayer].lives - 1
              }
            }));
          } else {
            setGameState(prev => ({ ...prev, lives: prev.lives - 1 }));
          }
          return false;
        }
        return balloon.health > 0;
      });
      
      return updated;
    });
    
    // Update explosions
    setExplosions(prev => prev.map(explosion => {
      const elapsed = currentTime - explosion.startTime;
      const progress = elapsed / explosion.duration;
      
      return {
        ...explosion,
        radius: explosion.maxRadius * Math.min(progress, 1),
        alpha: Math.max(0, 1 - progress)
      };
    }).filter(explosion => currentTime - explosion.startTime < explosion.duration));
    
    // Update projectiles
    setProjectiles(prev => prev.map(proj => ({
      ...proj,
      x: proj.x + proj.vx,
      y: proj.y + proj.vy,
      distanceTraveled: proj.distanceTraveled + Math.sqrt(proj.vx * proj.vx + proj.vy * proj.vy)
    })).filter(proj => {
      return proj.distanceTraveled < 600 && 
             proj.x >= 0 && proj.x <= CANVAS_WIDTH && 
             proj.y >= 0 && proj.y <= CANVAS_HEIGHT;
    }));
    
    // Tower firing logic
    setTowers(prev => prev.map(tower => {
      const fireInterval = 1000 / tower.fireRate;
      
      if (currentTime - tower.lastFired > fireInterval) {
        const targetsInRange = balloons.filter(balloon => {
          const pos = getPathPosition(balloon.progress);
          const dist = distance({ x: tower.x, y: tower.y }, pos);
          return dist <= tower.range && balloon.progress >= 0;
        }).sort((a, b) => b.progress - a.progress); // Target furthest along path
        
        if (targetsInRange.length > 0) {
          const target = targetsInRange[0];
          const targetPos = getPathPosition(target.progress);
          
          // Create projectiles based on tower type
          const newProjectiles = [];
          
          if (tower.type === 'tack') {
            // Tack shooter shoots in all directions
            const angleStep = tower.spreadAngle / tower.projectileCount;
            for (let i = 0; i < tower.projectileCount; i++) {
              const angle = (i * angleStep) * Math.PI / 180;
              newProjectiles.push({
                id: Date.now() + Math.random(),
                x: tower.x,
                y: tower.y,
                vx: Math.cos(angle) * tower.projectileSpeed,
                vy: Math.sin(angle) * tower.projectileSpeed,
                damage: tower.damage,
                type: tower.type,
                distanceTraveled: 0,
                explosionRadius: tower.explosionRadius || 0
              });
            }
          } else if (tower.type === 'ice') {
            // Ice tower freezes balloons in range immediately
            setBalloons(prev => prev.map(balloon => {
              const pos = getPathPosition(balloon.progress);
              const dist = distance({ x: tower.x, y: tower.y }, pos);
              if (dist <= tower.range && !balloon.immuneTo?.includes('freeze') && balloon.progress >= 0) {
                return {
                  ...balloon,
                  iceSlowed: true,
                  iceSlowEndTime: currentTime + tower.slowDuration,
                  iceSlowAmount: tower.slowAmount
                };
              }
              return balloon;
            }));
            
            return { ...tower, lastFired: currentTime };
          } else if (tower.type === 'glue') {
            // Glue gunner shoots glue projectiles
            const angle = Math.atan2(targetPos.y - tower.y, targetPos.x - tower.x);
            newProjectiles.push({
              id: Date.now() + Math.random(),
              x: tower.x,
              y: tower.y,
              vx: Math.cos(angle) * tower.projectileSpeed,
              vy: Math.sin(angle) * tower.projectileSpeed,
              damage: tower.damage,
              type: tower.type,
              distanceTraveled: 0,
              targetId: target.id,
              isGlue: true,
              slowAmount: tower.slowAmount,
              slowDuration: tower.slowDuration,
              isCorrosive: tower.upgradeLevel?.path2 >= 1 // Corrosive glue upgrade
            });
          } else {
            // Regular projectile towers
            const angle = Math.atan2(targetPos.y - tower.y, targetPos.x - tower.x);
            
            for (let i = 0; i < tower.projectileCount; i++) {
              let projectileAngle = angle;
              
              if (tower.projectileCount > 1 && tower.spreadAngle) {
                const spread = (tower.spreadAngle * Math.PI / 180) / (tower.projectileCount - 1);
                projectileAngle = angle - (tower.spreadAngle * Math.PI / 360) + (i * spread);
              }
              
              newProjectiles.push({
                id: Date.now() + Math.random() + i,
                x: tower.x,
                y: tower.y,
                vx: Math.cos(projectileAngle) * tower.projectileSpeed,
                vy: Math.sin(projectileAngle) * tower.projectileSpeed,
                damage: tower.damage,
                type: tower.type,
                distanceTraveled: 0,
                explosionRadius: tower.explosionRadius || 0,
                targetId: target.id
              });
            }
          }
          
          if (newProjectiles.length > 0) {
            setProjectiles(prev => [...prev, ...newProjectiles]);
          }
          
          return { ...tower, lastFired: currentTime };
        }
      }
      return tower;
    }));
    
    // Projectile collision detection
    projectiles.forEach(projectile => {
      balloons.forEach(balloon => {
        const balloonPos = getPathPosition(balloon.progress);
        const dist = distance(projectile, balloonPos);
        
        if (dist < 15) { // Hit detection radius
          // Check immunities
          let canHit = true;
          if (projectile.type === 'dart' && balloon.immuneTo?.includes('sharp')) canHit = false;
          if (projectile.type === 'bomb' && balloon.immuneTo?.includes('explosion')) canHit = false;
          if (projectile.type === 'wizard' && balloon.immuneTo?.includes('magic')) canHit = false;
          
          if (canHit) {
            // Handle glue projectiles
            if (projectile.isGlue) {
              setBalloons(prev => prev.map(b => {
                if (b.id === balloon.id) {
                  const updatedBalloon = {
                    ...b,
                    glued: true,
                    glueEndTime: currentTime + projectile.slowDuration,
                    glueSlowAmount: projectile.slowAmount
                  };
                  
                  // Corrosive Glue upgrade - deals damage over time
                  if (projectile.isCorrosive) {
                    updatedBalloon.corrosive = true;
                    updatedBalloon.corrosiveEndTime = currentTime + projectile.slowDuration;
                    updatedBalloon.lastCorrosiveDamage = currentTime;
                  }
                  
                  return updatedBalloon;
                }
                return b;
              }));
              
              // Remove glue projectile after hit
              setProjectiles(prev => prev.filter(p => p.id !== projectile.id));
              return; // Don't process damage for glue
            }
            
            // Handle bomb explosions
            if (projectile.type === 'bomb' && projectile.explosionRadius) {
              const explosionPos = { x: projectile.x, y: projectile.y };
              
              // Add explosion visual effect
              setExplosions(prev => [...prev, {
                id: Date.now() + Math.random(),
                x: explosionPos.x,
                y: explosionPos.y,
                radius: 0,
                maxRadius: projectile.explosionRadius,
                startTime: currentTime,
                duration: 300,
                alpha: 1
              }]);
              
              setBalloons(prev => prev.map(b => {
                const balloonPos = getPathPosition(b.progress);
                const distToExplosion = distance(balloonPos, explosionPos);
                
                if (distToExplosion <= projectile.explosionRadius && !b.immuneTo?.includes('explosion')) {
                  const newHealth = b.health - projectile.damage;
                  if (newHealth <= 0) {
                    // Balloon destroyed - spawn children and give money
                    const reward = BALLOON_TYPES[b.type].reward;
                    
                    if (gameMode === 'multiplayer') {
                      const playerKey = b.sentByPlayer === 1 ? 'player2' : 'player1';
                      setGameState(prev => ({
                        ...prev,
                        [playerKey]: {
                          ...prev[playerKey],
                          money: prev[playerKey].money + reward,
                          score: prev[playerKey].score + reward
                        }
                      }));
                    } else {
                      setGameState(prev => ({
                        ...prev,
                        money: prev.money + reward,
                        score: prev.score + reward
                      }));
                    }
                    
                    // Spawn children
                    if (b.children && b.children.length > 0) {
                      setTimeout(() => {
                        const childBalloons = b.children.map(childType => ({
                          id: Date.now() + Math.random(),
                          type: childType,
                          ...BALLOON_TYPES[childType],
                          progress: b.progress,
                          iceSlowed: false,
                          iceSlowEndTime: 0,
                          glued: false,
                          glueEndTime: 0,
                          sentByPlayer: b.sentByPlayer
                        }));
                        setBalloons(prev => [...prev, ...childBalloons]);
                      }, 50);
                    }
                    
                    return null; // Remove balloon
                  }
                  return { ...b, health: newHealth };
                }
                return b;
              }).filter(Boolean));
              
              // Remove bomb projectile after explosion
              setProjectiles(prev => prev.filter(p => p.id !== projectile.id));
              return; // Don't process single-target damage for bombs
            }
            
            setBalloons(prev => prev.map(b => {
              if (b.id === balloon.id) {
                const newHealth = b.health - projectile.damage;
                if (newHealth <= 0) {
                  // Balloon destroyed - spawn children and give money
                  const reward = BALLOON_TYPES[b.type].reward;
                  
                  if (gameMode === 'multiplayer') {
                    const playerKey = b.sentByPlayer === 1 ? 'player2' : 'player1';
                    setGameState(prev => ({
                      ...prev,
                      [playerKey]: {
                        ...prev[playerKey],
                        money: prev[playerKey].money + reward,
                        score: prev[playerKey].score + reward
                      }
                    }));
                  } else {
                    setGameState(prev => ({
                      ...prev,
                      money: prev.money + reward,
                      score: prev.score + reward
                    }));
                  }
                  
                  // Spawn children
                  if (b.children && b.children.length > 0) {
                    setTimeout(() => {
                      const childBalloons = b.children.map(childType => ({
                        id: Date.now() + Math.random(),
                        type: childType,
                        ...BALLOON_TYPES[childType],
                        progress: b.progress,
                        iceSlowed: false,
                        iceSlowEndTime: 0,
                        sentByPlayer: b.sentByPlayer
                      }));
                      setBalloons(prev => [...prev, ...childBalloons]);
                    }, 50);
                  }
                  
                  return null; // Remove balloon
                }
                return { ...b, health: newHealth };
              }
              return b;
            }).filter(Boolean));
            
            // Remove projectile after hit (unless it can hit multiple)
            if (!TOWER_TYPES[projectile.type].canHitMultiple) {
              setProjectiles(prev => prev.filter(p => p.id !== projectile.id));
            }
          }
        }
      });
    });
  }, [gameState, balloons, projectiles, towers, gameMode, isPlayer1Turn]);
  
  // Game render function
  const render = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const currentTrack = getAllTracks()[selectedTrack];
    
    // Clear canvas
    ctx.fillStyle = currentTrack.background;
    ctx.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    
    // Draw path
    ctx.strokeStyle = currentTrack.pathBorder;
    ctx.lineWidth = 32;
    ctx.lineCap = 'round';
    ctx.lineJoin = 'round';
    
    ctx.beginPath();
    ctx.moveTo(PATH[0].x, PATH[0].y);
    for (let i = 1; i < PATH.length; i++) {
      ctx.lineTo(PATH[i].x, PATH[i].y);
    }
    ctx.stroke();
    
    ctx.strokeStyle = currentTrack.pathColor;
    ctx.lineWidth = 28;
    ctx.beginPath();
    ctx.moveTo(PATH[0].x, PATH[0].y);
    for (let i = 1; i < PATH.length; i++) {
      ctx.lineTo(PATH[i].x, PATH[i].y);
    }
    ctx.stroke();
    
    // Draw towers
    towers.forEach(tower => {
      // Tower range (if selected)
      if (selectedTower === tower.id) {
        ctx.beginPath();
        ctx.arc(tower.x, tower.y, tower.range, 0, Math.PI * 2);
        ctx.fillStyle = 'rgba(255, 255, 255, 0.2)';
        ctx.fill();
        ctx.strokeStyle = 'rgba(255, 255, 255, 0.5)';
        ctx.lineWidth = 2;
        ctx.stroke();
      }
      
      // Tower body
      ctx.fillStyle = tower.color;
      ctx.beginPath();
      ctx.arc(tower.x, tower.y, 15, 0, Math.PI * 2);
      ctx.fill();
      
      // Tower border
      ctx.strokeStyle = '#000';
      ctx.lineWidth = 2;
      ctx.stroke();
      
      // Upgrade indicators
      const upgradeSum = Object.values(tower.upgradeLevel).reduce((sum, level) => sum + level, 0);
      if (upgradeSum > 0) {
        ctx.fillStyle = '#FFD700';
        ctx.beginPath();
        ctx.arc(tower.x + 12, tower.y - 12, 4, 0, Math.PI * 2);
        ctx.fill();
        
        ctx.fillStyle = '#000';
        ctx.font = '8px Arial';
        ctx.textAlign = 'center';
        ctx.fillText(upgradeSum.toString(), tower.x + 12, tower.y - 8);
      }
      
      // Player indicator for multiplayer
      if (gameMode === 'multiplayer') {
        ctx.fillStyle = tower.owner === 1 ? '#FF0000' : '#0000FF';
        ctx.beginPath();
        ctx.arc(tower.x - 12, tower.y - 12, 3, 0, Math.PI * 2);
        ctx.fill();
      }
    });
    
    // Draw balloons
    balloons.forEach(balloon => {
      if (balloon.progress >= 0) {
        const pos = getPathPosition(balloon.progress);
        
        // Determine balloon size based on type
        let balloonSize = 12;
        if (balloon.isMoab) {
          balloonSize = balloon.type === 'bad' ? 35 : 
                       balloon.type === 'zomg' ? 30 :
                       balloon.type === 'bfb' ? 25 :
                       balloon.type === 'ddt' ? 18 : 20; // moab
        }
        
        // Special balloon effects
        if (balloon.camo) {
          // Camo effect - flickering transparency
          const time = Date.now() * 0.005;
          ctx.globalAlpha = 0.3 + 0.4 * Math.sin(time * 2);
        }
        
        if (balloon.regrow) {
          // Regrow effect - pulsing size
          const time = Date.now() * 0.003;
          balloonSize += Math.sin(time * 3) * 2;
        }
        
        // Balloon body
        ctx.fillStyle = balloon.color;
        ctx.beginPath();
        ctx.arc(pos.x, pos.y, balloonSize, 0, Math.PI * 2);
        ctx.fill();
        
        // Special visual effects for different balloon types
        if (balloon.isMoab) {
          // MOAB class balloons have distinct patterns
          ctx.strokeStyle = '#FFFFFF';
          ctx.lineWidth = 3;
          ctx.stroke();
          
          // Add type-specific patterns
          if (balloon.type === 'bfb') {
            ctx.fillStyle = '#000000';
            for (let i = 0; i < 4; i++) {
              const angle = i * Math.PI / 2;
              const stripX = pos.x + Math.cos(angle) * balloonSize * 0.6;
              const stripY = pos.y + Math.sin(angle) * balloonSize * 0.6;
              ctx.beginPath();
              ctx.arc(stripX, stripY, 3, 0, Math.PI * 2);
              ctx.fill();
            }
          } else if (balloon.type === 'zomg') {
            ctx.fillStyle = '#FFFF00';
            ctx.beginPath();
            ctx.arc(pos.x, pos.y, balloonSize * 0.3, 0, Math.PI * 2);
            ctx.fill();
          } else if (balloon.type === 'bad') {
            ctx.fillStyle = '#FFFFFF';
            ctx.beginPath();
            ctx.arc(pos.x - balloonSize * 0.3, pos.y - balloonSize * 0.3, 4, 0, Math.PI * 2);
            ctx.fill();
            ctx.beginPath();
            ctx.arc(pos.x + balloonSize * 0.3, pos.y - balloonSize * 0.3, 4, 0, Math.PI * 2);
            ctx.fill();
          } else if (balloon.type === 'ddt') {
            // DDT has dark metallic appearance with rivets
            ctx.fillStyle = '#1C1C1C';
            for (let i = 0; i < 6; i++) {
              const angle = i * Math.PI / 3;
              const rivetX = pos.x + Math.cos(angle) * balloonSize * 0.7;
              const rivetY = pos.y + Math.sin(angle) * balloonSize * 0.7;
              ctx.beginPath();
              ctx.arc(rivetX, rivetY, 2, 0, Math.PI * 2);
              ctx.fill();
            }
          }
        } else {
          // Regular balloon border
          ctx.strokeStyle = '#000';
          ctx.lineWidth = 2;
          ctx.stroke();
        }
        
        // Fortified effect - golden armor plating
        if (balloon.fortified) {
          ctx.strokeStyle = '#FFD700';
          ctx.lineWidth = 4;
          ctx.beginPath();
          ctx.arc(pos.x, pos.y, balloonSize + 2, 0, Math.PI * 2);
          ctx.stroke();
          
          // Armor segments
          for (let i = 0; i < 8; i++) {
            const angle = i * Math.PI / 4;
            const segmentX = pos.x + Math.cos(angle) * (balloonSize + 2);
            const segmentY = pos.y + Math.sin(angle) * (balloonSize + 2);
            ctx.fillStyle = '#B8860B';
            ctx.beginPath();
            ctx.arc(segmentX, segmentY, 2, 0, Math.PI * 2);
            ctx.fill();
          }
        }
        
        // Reset alpha for other effects
        if (balloon.camo) {
          ctx.globalAlpha = 1;
        }
        
        // Ice slow effect
        if (balloon.iceSlowed) {
          ctx.fillStyle = 'rgba(173, 216, 230, 0.7)';
          ctx.beginPath();
          ctx.arc(pos.x, pos.y, balloonSize + 4, 0, Math.PI * 2);
          ctx.fill();
          
          // Ice crystals effect
          const time = Date.now() * 0.005;
          for (let i = 0; i < 6; i++) {
            const angle = (time + i * Math.PI / 3) % (Math.PI * 2);
            const crystalX = pos.x + Math.cos(angle) * (balloonSize + 6);
            const crystalY = pos.y + Math.sin(angle) * (balloonSize + 6);
            ctx.fillStyle = 'rgba(200, 200, 255, 0.8)';
            ctx.beginPath();
            ctx.arc(crystalX, crystalY, 2, 0, Math.PI * 2);
            ctx.fill();
          }
        }
        
        // Glue effect
        if (balloon.glued) {
          ctx.fillStyle = 'rgba(218, 165, 32, 0.7)';
          ctx.beginPath();
          ctx.arc(pos.x, pos.y, balloonSize + 2, 0, Math.PI * 2);
          ctx.fill();
          
          // Dripping glue effect
          const time = Date.now() * 0.003;
          for (let i = 0; i < 4; i++) {
            const angle = i * Math.PI / 2;
            const dripX = pos.x + Math.cos(angle) * (balloonSize + 4);
            const dripY = pos.y + Math.sin(angle) * (balloonSize + 4) + Math.sin(time + i) * 3;
            ctx.fillStyle = 'rgba(184, 134, 11, 0.9)';
            ctx.beginPath();
            ctx.arc(dripX, dripY, 3, 0, Math.PI * 2);
            ctx.fill();
          }
        }
        
        // Corrosive effect
        if (balloon.corrosive) {
          ctx.fillStyle = 'rgba(50, 205, 50, 0.6)';
          ctx.beginPath();
          ctx.arc(pos.x, pos.y, balloonSize + 6, 0, Math.PI * 2);
          ctx.fill();
          
          // Bubbling effect for corrosive
          const time = Date.now() * 0.01;
          for (let i = 0; i < 5; i++) {
            const angle = (time + i * 1.2) % (Math.PI * 2);
            const bubbleX = pos.x + Math.cos(angle) * (balloonSize + Math.sin(time * 2 + i) * 2);
            const bubbleY = pos.y + Math.sin(angle) * (balloonSize + Math.cos(time * 2 + i) * 2);
            ctx.fillStyle = 'rgba(0, 255, 0, 0.8)';
            ctx.beginPath();
            ctx.arc(bubbleX, bubbleY, 2 + Math.sin(time * 3 + i) * 0.5, 0, Math.PI * 2);
            ctx.fill();
          }
        }
        
        // Health bar for stronger balloons
        if (balloon.health > 5 || balloon.isMoab) {
          const maxHealth = BALLOON_TYPES[balloon.type].health;
          const healthPercent = balloon.health / maxHealth;
          
          const barWidth = Math.max(20, balloonSize * 1.5);
          const barY = pos.y - balloonSize - 8;
          
          ctx.fillStyle = '#FF0000';
          ctx.fillRect(pos.x - barWidth/2, barY, barWidth, 4);
          ctx.fillStyle = '#00FF00';
          ctx.fillRect(pos.x - barWidth/2, barY, barWidth * healthPercent, 4);
          
          // Health text for MOAB class
          if (balloon.isMoab) {
            ctx.fillStyle = '#FFFFFF';
            ctx.font = '10px Arial';
            ctx.textAlign = 'center';
            ctx.fillText(balloon.health.toString(), pos.x, barY - 2);
          }
        }
        
        // Player indicator for multiplayer
        if (gameMode === 'multiplayer' && balloon.sentByPlayer > 0) {
          ctx.fillStyle = balloon.sentByPlayer === 1 ? '#FF0000' : '#0000FF';
          ctx.beginPath();
          ctx.arc(pos.x - balloonSize - 4, pos.y - balloonSize - 4, 3, 0, Math.PI * 2);
          ctx.fill();
        }
      }
    });
    
    // Draw projectiles
    projectiles.forEach(projectile => {
      if (projectile.type === 'bomb') {
        // Bomb projectile - larger and darker
        ctx.fillStyle = '#4A4A4A';
        ctx.beginPath();
        ctx.arc(projectile.x, projectile.y, 5, 0, Math.PI * 2);
        ctx.fill();
        ctx.strokeStyle = '#000';
        ctx.lineWidth = 1;
        ctx.stroke();
      } else if (projectile.isGlue) {
        // Glue projectile - golden color with trail
        ctx.fillStyle = '#DAA520';
        ctx.beginPath();
        ctx.arc(projectile.x, projectile.y, 4, 0, Math.PI * 2);
        ctx.fill();
        
        // Glue trail effect
        ctx.fillStyle = 'rgba(218, 165, 32, 0.3)';
        ctx.beginPath();
        ctx.arc(projectile.x - projectile.vx, projectile.y - projectile.vy, 3, 0, Math.PI * 2);
        ctx.fill();
      } else {
        // Regular projectile
        ctx.fillStyle = '#FFD700';
        ctx.beginPath();
        ctx.arc(projectile.x, projectile.y, 3, 0, Math.PI * 2);
        ctx.fill();
      }
    });
    
    // Draw explosions
    explosions.forEach(explosion => {
      ctx.save();
      ctx.globalAlpha = explosion.alpha || 1;
      
      // Orange explosion effect
      const gradient = ctx.createRadialGradient(
        explosion.x, explosion.y, 0,
        explosion.x, explosion.y, explosion.radius
      );
      gradient.addColorStop(0, '#FF6600');
      gradient.addColorStop(0.5, '#FF3300');
      gradient.addColorStop(1, 'rgba(255, 0, 0, 0)');
      
      ctx.fillStyle = gradient;
      ctx.beginPath();
      ctx.arc(explosion.x, explosion.y, explosion.radius, 0, Math.PI * 2);
      ctx.fill();
      
      ctx.restore();
    });
    
    // Draw placement preview
    if (placingTower) {
      ctx.fillStyle = 'rgba(255, 255, 255, 0.5)';
      ctx.beginPath();
      ctx.arc(placingTower.x, placingTower.y, 15, 0, Math.PI * 2);
      ctx.fill();
      
      // Show range
      const towerType = TOWER_TYPES[placingTower.type];
      ctx.beginPath();
      ctx.arc(placingTower.x, placingTower.y, towerType.range, 0, Math.PI * 2);
      ctx.strokeStyle = 'rgba(255, 255, 255, 0.3)';
      ctx.lineWidth = 2;
      ctx.stroke();
    }
  }, [selectedTrack, towers, balloons, projectiles, explosions, selectedTower, placingTower, gameMode]);

  // Animation loop
  useEffect(() => {
    const animate = () => {
      gameLoop();
      render();
      animationRef.current = requestAnimationFrame(animate);
    };
    
    if (gameMode === 'singleplayer' || gameMode === 'multiplayer' || gameMode === 'sandbox') {
      animationRef.current = requestAnimationFrame(animate);
    }
    
    return () => {
      if (animationRef.current) {
        cancelAnimationFrame(animationRef.current);
      }
    };
  }, [gameLoop, render, gameMode]);
  
  // Check game over conditions
  useEffect(() => {
    if (gameMode === 'singleplayer' && gameState.lives <= 0) {
      setGameState(prev => ({ ...prev, isGameOver: true }));
    }
    if (gameMode === 'multiplayer') {
      if (gameState.player1.lives <= 0 || gameState.player2.lives <= 0) {
        setGameState(prev => ({ ...prev, isGameOver: true }));
      }
    }
  }, [gameState.lives, gameState.player1.lives, gameState.player2.lives, gameMode]);
  
  // Wave progression
  useEffect(() => {
    if (waveCompleted && balloons.length === 0 && !waveInProgress) {
      setTimeout(() => {
        setGameState(prev => ({ 
          ...prev, 
          wave: prev.wave + 1,
          money: prev.money + (prev.wave * 50) // Bonus money for completing wave
        }));
        setWaveCompleted(false);
      }, 1000);
    }
  }, [waveCompleted, balloons.length, waveInProgress]);
  
  // Canvas click handler
  const handleCanvasClick = (e) => {
    const canvas = canvasRef.current;
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    
    if (placingTower) {
      // Check if click is not on path
      let onPath = false;
      for (let i = 0; i < PATH.length - 1; i++) {
        const start = PATH[i];
        const end = PATH[i + 1];
        const pathDist = distanceToLineSegment({ x, y }, start, end);
        if (pathDist < 25) {
          onPath = true;
          break;
        }
      }
      
      if (!onPath) {
        placeTower(x, y, placingTower.type);
      }
      return;
    }
    
    // Check if clicking on a tower
    let clickedTower = null;
    towers.forEach(tower => {
      if (distance({ x, y }, tower) < 20) {
        clickedTower = tower.id;
      }
    });
    
    setSelectedTower(clickedTower);
  };
  
  // Distance to line segment helper function
  const distanceToLineSegment = (point, lineStart, lineEnd) => {
    const A = point.x - lineStart.x;
    const B = point.y - lineStart.y;
    const C = lineEnd.x - lineStart.x;
    const D = lineEnd.y - lineStart.y;
    
    const dot = A * C + B * D;
    const lenSq = C * C + D * D;
    
    if (lenSq === 0) return distance(point, lineStart);
    
    let t = Math.max(0, Math.min(1, dot / lenSq));
    
    const projection = {
      x: lineStart.x + t * C,
      y: lineStart.y + t * D
    };
    
    return distance(point, projection);
  };
  
  // Track mouse movement for tower placement preview
  const handleMouseMove = (e) => {
    if (placingTower) {
      const canvas = canvasRef.current;
      const rect = canvas.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const y = e.clientY - rect.top;
      setPlacingTower(prev => ({ ...prev, x, y }));
    }
  };
  
  // Send balloons function for multiplayer and sandbox
  const sendBalloons = (type, count) => {
    if (gameMode !== 'multiplayer' && gameMode !== 'sandbox') return;
    
    const balloonData = BALLOON_TYPES[type];
    const totalCost = balloonData.cost * count;
    
    if (gameMode === 'sandbox') {
      // In sandbox mode, spawn balloons immediately without cost
      for (let i = 0; i < count; i++) {
        setTimeout(() => {
          setBalloons(prev => [...prev, {
            id: Date.now() + Math.random(),
            type,
            ...balloonData,
            progress: -0.05 - i * 0.02,
            iceSlowed: false,
            iceSlowEndTime: 0,
            glued: false,
            glueEndTime: 0,
            corrosive: false,
            corrosiveEndTime: 0,
            sentByPlayer: 0
          }]);
        }, i * 200);
      }
    } else if (gameMode === 'multiplayer') {
      const currentPlayer = isPlayer1Turn ? gameState.player1 : gameState.player2;
      
      if (currentPlayer.money >= totalCost) {
        const playerKey = isPlayer1Turn ? 'player1' : 'player2';
        setGameState(prev => ({
          ...prev,
          [playerKey]: {
            ...prev[playerKey],
            money: prev[playerKey].money - totalCost
          }
        }));
        
        for (let i = 0; i < count; i++) {
          setTimeout(() => {
            setBalloons(prev => [...prev, {
              id: Date.now() + Math.random(),
              type,
              ...balloonData,
              progress: -0.05 - i * 0.02,
              iceSlowed: false,
              iceSlowEndTime: 0,
              glued: false,
              glueEndTime: 0,
              corrosive: false,
              corrosiveEndTime: 0,
              sentByPlayer: isPlayer1Turn ? 1 : 2
            }]);
          }, i * 200);
        }
        
        setIsPlayer1Turn(!isPlayer1Turn);
      }
    }
  };
  
  // Render UI components
  if (gameMode === 'menu') {
    return (
      <div className="flex flex-col items-center justify-center min-h-screen bg-gradient-to-b from-blue-400 to-green-400 p-4">
        <div className="bg-white rounded-lg shadow-2xl p-8 max-w-md w-full">
          <h1 className="text-4xl font-bold text-center mb-8 text-gray-800">Tower Defense</h1>
          
          <div className="space-y-4">
            <button
              onClick={() => setGameMode('singleplayer')}
              className="w-full bg-blue-500 hover:bg-blue-600 text-white font-bold py-3 px-4 rounded-lg transition-colors"
            >
              Single Player
            </button>
            
            <button
              onClick={() => setGameMode('multiplayer')}
              className="w-full bg-red-500 hover:bg-red-600 text-white font-bold py-3 px-4 rounded-lg transition-colors"
            >
              Multiplayer
            </button>
            
            <button
              onClick={() => setGameMode('sandbox')}
              className="w-full bg-purple-500 hover:bg-purple-600 text-white font-bold py-3 px-4 rounded-lg transition-colors"
            >
              Sandbox Mode
            </button>
            
            <div className="border-t pt-4">
              <h3 className="font-bold mb-2 text-gray-700">Select Track:</h3>
              <select
                value={selectedTrack}
                onChange={(e) => setSelectedTrack(e.target.value)}
                className="w-full p-2 border border-gray-300 rounded"
              >
                {Object.entries(TRACKS).map(([key, track]) => (
                  <option key={key} value={key}>{track.name}</option>
                ))}
              </select>
            </div>
          </div>
        </div>
      </div>
    );
  }
  
  const currentMoney = gameMode === 'sandbox' ? 999999 : // Infinite money display in sandbox
    gameMode === 'multiplayer' ? 
      (isPlayer1Turn ? gameState.player1.money : gameState.player2.money) : gameState.money;
  
  return (
    <div className="flex flex-col h-screen bg-gray-800">
      {/* Game Info Bar */}
      <div className="bg-gray-700 text-white p-3 flex justify-between items-center flex-wrap">
        {gameMode === 'singleplayer' ? (
          <>
            <div className="flex space-x-4">
              <span>Lives: {gameState.lives}</span>
              <span>Money: ${gameState.money}</span>
              <span>Wave: {gameState.wave}</span>
              <span>Score: {gameState.score}</span>
            </div>
            
            <div className="flex space-x-2">
              <button
                onClick={spawnWave}
                disabled={waveInProgress}
                className={`px-4 py-2 rounded font-bold ${
                  waveInProgress 
                    ? 'bg-gray-500 cursor-not-allowed' 
                    : 'bg-green-500 hover:bg-green-600'
                } text-white`}
              >
                {waveInProgress ? 'Wave in Progress' : 'Start Wave'}
              </button>
              
              <button
                onClick={() => setGameState(prev => ({ ...prev, isPaused: !prev.isPaused }))}
                className="bg-yellow-500 hover:bg-yellow-600 text-white px-4 py-2 rounded font-bold"
              >
                {gameState.isPaused ? 'Resume' : 'Pause'}
              </button>
              
              <button
                onClick={() => setGameMode('menu')}
                className="bg-red-500 hover:bg-red-600 text-white px-4 py-2 rounded font-bold"
              >
                Menu
              </button>
            </div>
          </>
        ) : gameMode === 'sandbox' ? (
          <>
            <div className="flex space-x-4">
              <span>Money: Unlimited ∞</span>
              <span className="text-purple-400">Sandbox Mode</span>
            </div>
            
            <div className="flex space-x-2">
              <button
                onClick={() => setGameState(prev => ({ ...prev, isPaused: !prev.isPaused }))}
                className="bg-yellow-500 hover:bg-yellow-600 text-white px-4 py-2 rounded font-bold"
              >
                {gameState.isPaused ? 'Resume' : 'Pause'}
              </button>
              
              <button
                onClick={() => {
                  setBalloons([]);
                  setProjectiles([]);
                  setExplosions([]);
                }}
                className="bg-orange-500 hover:bg-orange-600 text-white px-4 py-2 rounded font-bold"
              >
                Clear Balloons
              </button>
              
              <button
                onClick={() => setGameMode('menu')}
                className="bg-red-500 hover:bg-red-600 text-white px-4 py-2 rounded font-bold"
              >
                Menu
              </button>
            </div>
          </>
        ) : (
          <>
            <div className="flex space-x-6">
              <div className="text-red-400">
                P1 - Lives: {gameState.player1.lives} | Money: ${gameState.player1.money} | Score: {gameState.player1.score}
              </div>
              <div className="text-blue-400">
                P2 - Lives: {gameState.player2.lives} | Money: ${gameState.player2.money} | Score: {gameState.player2.score}
              </div>
            </div>
            
            <div className="flex items-center space-x-4">
              <span className={isPlayer1Turn ? 'text-red-400' : 'text-blue-400'}>
                {isPlayer1Turn ? 'Player 1 Turn' : 'Player 2 Turn'}
              </span>
              
              <button
                onClick={() => setGameMode('menu')}
                className="bg-red-500 hover:bg-red-600 text-white px-4 py-2 rounded font-bold"
              >
                Menu
              </button>
            </div>
          </>
        )}
      </div>
      
      <div className="flex flex-1">
        {/* Game Canvas */}
        <div className="flex-1 flex justify-center items-center bg-gray-900">
          <canvas
            ref={canvasRef}
            width={CANVAS_WIDTH}
            height={CANVAS_HEIGHT}
            onClick={handleCanvasClick}
            onMouseMove={handleMouseMove}
            className="border-2 border-gray-600 cursor-crosshair"
          />
        </div>
        
        {/* Side Panel */}
        <div className="w-64 bg-gray-700 text-white p-4 overflow-y-auto">
          {/* Tower Shop */}
          <div className="mb-6">
            <h3 className="text-lg font-bold mb-3">Tower Shop</h3>
            <div className="grid grid-cols-1 gap-2">
              {Object.entries(TOWER_TYPES).map(([type, tower]) => (
                <button
                  key={type}
                  onClick={() => setPlacingTower({ type, x: 0, y: 0 })}
                  disabled={currentMoney < tower.cost}
                  className={`p-2 rounded text-left text-sm ${
                    currentMoney >= tower.cost
                      ? 'bg-blue-600 hover:bg-blue-700'
                      : 'bg-gray-500 cursor-not-allowed'
                  }`}
                >
                  <div className="font-bold">{tower.name}</div>
                  <div className="text-xs">${tower.cost}</div>
                </button>
              ))}
            </div>
          </div>
          
          {/* Balloon Shop for Multiplayer and Sandbox */}
          {(gameMode === 'multiplayer' || gameMode === 'sandbox') && (
            <div className="mb-6">
              <h3 className="text-lg font-bold mb-3">
                {gameMode === 'sandbox' ? 'Spawn Balloons' : 'Send Balloons'}
              </h3>
              
              {/* Basic Balloons */}
              <div className="mb-3">
                <h4 className="text-sm font-bold mb-2 text-gray-300">Basic Balloons</h4>
                <div className="grid grid-cols-2 gap-1">
                  {Object.entries(BALLOON_TYPES).slice(0, 5).map(([type, balloon]) => (
                    <button
                      key={type}
                      onClick={() => sendBalloons(type, 1)}
                      disabled={gameMode === 'multiplayer' && currentMoney < balloon.cost}
                      className={`p-2 rounded text-left text-xs ${
                        gameMode === 'sandbox' || currentMoney >= balloon.cost
                          ? gameMode === 'sandbox' 
                            ? 'bg-purple-600 hover:bg-purple-700'
                            : 'bg-red-600 hover:bg-red-700'
                          : 'bg-gray-500 cursor-not-allowed'
                      }`}
                      style={{ color: balloon.color === '#FFFFFF' ? '#000' : balloon.color }}
                    >
                      <div className="font-bold">{type.toUpperCase()}</div>
                      <div>{gameMode === 'sandbox' ? 'FREE' : `${balloon.cost}`}</div>
                    </button>
                  ))}
                </div>
              </div>
              
              {/* Special Balloons */}
              <div className="mb-3">
                <h4 className="text-sm font-bold mb-2 text-gray-300">Special Balloons</h4>
                <div className="grid grid-cols-2 gap-1">
                  {['black', 'white', 'lead', 'zebra', 'purple', 'camo_green', 'camo_lead', 'regrow_blue'].map((type) => {
                    const balloon = BALLOON_TYPES[type];
                    return (
                      <button
                        key={type}
                        onClick={() => sendBalloons(type, 1)}
                        disabled={gameMode === 'multiplayer' && currentMoney < balloon.cost}
                        className={`p-1 rounded text-left text-xs ${
                          gameMode === 'sandbox' || currentMoney >= balloon.cost
                            ? gameMode === 'sandbox' 
                              ? 'bg-purple-600 hover:bg-purple-700'
                              : 'bg-red-600 hover:bg-red-700'
                            : 'bg-gray-500 cursor-not-allowed'
                        }`}
                        style={{ color: balloon.color === '#FFFFFF' ? '#000' : balloon.color }}
                      >
                        <div className="font-bold text-xs">{type.replace('_', ' ').toUpperCase()}</div>
                        <div className="text-xs">{gameMode === 'sandbox' ? 'FREE' : `${balloon.cost}`}</div>
                      </button>
                    );
                  })}
                </div>
              </div>
              
              {/* Strong Balloons */}
              <div className="mb-3">
                <h4 className="text-sm font-bold mb-2 text-gray-300">Strong Balloons</h4>
                <div className="grid grid-cols-1 gap-1">
                  {['rainbow', 'ceramic', 'fortified_ceramic', 'regrow_ceramic'].map((type) => {
                    const balloon = BALLOON_TYPES[type];
                    return (
                      <button
                        key={type}
                        onClick={() => sendBalloons(type, 1)}
                        disabled={gameMode === 'multiplayer' && currentMoney < balloon.cost}
                        className={`p-2 rounded text-left text-xs ${
                          gameMode === 'sandbox' || currentMoney >= balloon.cost
                            ? gameMode === 'sandbox' 
                              ? 'bg-purple-600 hover:bg-purple-700'
                              : 'bg-red-600 hover:bg-red-700'
                            : 'bg-gray-500 cursor-not-allowed'
                        }`}
                        style={{ color: balloon.color === '#FFFFFF' ? '#000' : balloon.color }}
                      >
                        <div className="font-bold">{type.replace('_', ' ').toUpperCase()}</div>
                        <div>{gameMode === 'sandbox' ? 'FREE' : `${balloon.cost}`}</div>
                      </button>
                    );
                  })}
                </div>
              </div>
              
              {/* MOAB Class */}
              <div className="mb-3">
                <h4 className="text-sm font-bold mb-2 text-red-400">MOAB Class</h4>
                <div className="grid grid-cols-1 gap-1">
                  {['moab', 'bfb', 'zomg', 'ddt', 'bad'].map((type) => {
                    const balloon = BALLOON_TYPES[type];
                    return (
                      <button
                        key={type}
                        onClick={() => sendBalloons(type, 1)}
                        disabled={gameMode === 'multiplayer' && currentMoney < balloon.cost}
                        className={`p-2 rounded text-left text-xs ${
                          gameMode === 'sandbox' || currentMoney >= balloon.cost
                            ? gameMode === 'sandbox' 
                              ? 'bg-purple-700 hover:bg-purple-800 border border-red-400'
                              : 'bg-red-700 hover:bg-red-800 border border-red-400'
                            : 'bg-gray-500 cursor-not-allowed'
                        }`}
                        style={{ color: balloon.color === '#FFFFFF' ? '#000' : balloon.color }}
                      >
                        <div className="font-bold">{type.toUpperCase()}</div>
                        <div className="text-yellow-300">{gameMode === 'sandbox' ? 'FREE' : `${balloon.cost}`}</div>
                      </button>
                    );
                  })}
                </div>
              </div>
              
              {gameMode === 'sandbox' && (
                <div className="mt-3 space-y-2">
                  <h4 className="font-bold text-sm">Quick Spawn:</h4>
                  <div className="grid grid-cols-2 gap-1">
                    <button
                      onClick={() => sendBalloons('red', 20)}
                      className="bg-red-500 hover:bg-red-600 text-white p-1 rounded text-xs"
                    >
                      20 Red
                    </button>
                    <button
                      onClick={() => sendBalloons('ceramic', 5)}
                      className="bg-orange-600 hover:bg-orange-700 text-white p-1 rounded text-xs"
                    >
                      5 Ceramic
                    </button>
                    <button
                      onClick={() => sendBalloons('moab', 3)}
                      className="bg-blue-600 hover:bg-blue-700 text-white p-1 rounded text-xs"
                    >
                      3 MOAB
                    </button>
                    <button
                      onClick={() => sendBalloons('bad', 1)}
                      className="bg-red-800 hover:bg-red-900 text-white p-1 rounded text-xs"
                    >
                      1 BAD
                    </button>
                  </div>
                  <button
                    onClick={() => {
                      sendBalloons('fortified_ceramic', 10);
                      setTimeout(() => sendBalloons('bfb', 2), 3000);
                      setTimeout(() => sendBalloons('zomg', 1), 6000);
                    }}
                    className="w-full bg-gradient-to-r from-red-600 to-purple-600 hover:from-red-700 hover:to-purple-700 text-white p-2 rounded text-xs font-bold"
                  >
                    Challenge Wave
                  </button>
                </div>
              )}
            </div>
          )}
          
          {/* Tower Upgrade Panel */}
          {selectedTower && (
            <div>
              <h3 className="text-lg font-bold mb-3">Tower Upgrades</h3>
              {(() => {
                const tower = towers.find(t => t.id === selectedTower);
                if (!tower) return null;
                
                return (
                  <div className="space-y-3">
                    <div className="text-sm">
                      <div className="font-bold">{tower.name}</div>
                      <div>Damage: {tower.damage}</div>
                      <div>Range: {tower.range}</div>
                      <div>Fire Rate: {tower.fireRate.toFixed(1)}</div>
                    </div>
                    
                    {Object.entries(tower.upgrades).map(([path, upgrades]) => (
                      <div key={path} className="border border-gray-600 p-2 rounded">
                        <div className="font-bold text-xs mb-1">Path {path.slice(-1)}</div>
                        {upgrades.map((upgrade, index) => {
                          const level = index + 1;
                          const isUpgraded = tower.upgradeLevel[path] >= level;
                          const canUpgrade = tower.upgradeLevel[path] === level - 1 && 
                                           (!tower.selectedPath || tower.selectedPath === path);
                          const cost = 100 + (level - 1) * 150;
                          
                          return (
                            <button
                              key={level}
                              onClick={() => upgradeTower(tower.id, path)}
                              disabled={!canUpgrade || currentMoney < cost}
                              className={`block w-full p-1 mb-1 rounded text-xs ${
                                isUpgraded
                                  ? 'bg-green-600'
                                  : canUpgrade && currentMoney >= cost
                                  ? 'bg-yellow-600 hover:bg-yellow-700'
                                  : 'bg-gray-500 cursor-not-allowed'
                              }`}
                            >
                              {upgrade} ${cost}
                            </button>
                          );
                        })}
                      </div>
                    ))}
                    
                    <button
                      onClick={() => sellTower(tower.id)}
                      className="w-full bg-red-600 hover:bg-red-700 text-white p-2 rounded text-sm font-bold"
                    >
                      Sell Tower
                    </button>
                  </div>
                );
              })()}
            </div>
          )}
        </div>
      </div>
      
      {/* Game Over Screen */}
      {gameState.isGameOver && (
        <div className="absolute inset-0 bg-black bg-opacity-75 flex items-center justify-center">
          <div className="bg-white p-8 rounded-lg text-center">
            <h2 className="text-3xl font-bold mb-4 text-gray-800">Game Over!</h2>
            {gameMode === 'singleplayer' ? (
              <p className="mb-4 text-gray-600">Final Score: {gameState.score}</p>
            ) : (
              <div className="mb-4 text-gray-600">
                <p>Player 1 Score: {gameState.player1.score}</p>
                <p>Player 2 Score: {gameState.player2.score}</p>
                <p className="font-bold mt-2">
                  Winner: {gameState.player1.lives > 0 ? 'Player 1' : 'Player 2'}!
                </p>
              </div>
            )}
            <button
              onClick={() => {
                setGameMode('menu');
                setGameState({
                  lives: 100,
                  money: 650,
                  wave: 1,
                  score: 0,
                  gameSpeed: 1,
                  isPaused: false,
                  isGameOver: false,
                  player1: { lives: 150, money: 650, score: 0 },
                  player2: { lives: 150, money: 650, score: 0 }
                });
                setTowers([]);
                setBalloons([]);
                setProjectiles([]);
                setExplosions([]);
                setSelectedTower(null);
                setPlacingTower(null);
                setWaveInProgress(false);
                setWaveCompleted(false);
              }}
              className="bg-blue-500 hover:bg-blue-600 text-white font-bold py-2 px-4 rounded"
            >
              Return to Menu
            </button>
          </div>
        </div>
      )}
    </div>
  );
};

export default Game;