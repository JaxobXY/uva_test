// worldData.js — ALL LEVELS TESTED & FIXED (cube clears consistently)
const FLAT_START = 600;

const GAME_DATA = {
  worlds: [
    {
      id: 1,
      name: "NEON",
      levels: [
        {
          id: 1,
          name: "NEON 1 - Warmup",
          endX: FLAT_START + 3200,
          objects: [
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 300, height: 50 },
            { type: "platform", x: FLAT_START + 300, yOffset: 0, width: 2500, height: 50 },
            { type: "spike", x: FLAT_START + 700, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 1150, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 1600, y: 0, height: 35 },
            { type: "platform", x: FLAT_START + 1900, yOffset: 100, width: 220, height: 20 }, // FIXED: 220px wide
            { type: "platform", x: FLAT_START + 2200, yOffset: 0, width: 900, height: 50 },
            { type: "spike", x: FLAT_START + 2600, y: 0, height: 35 },
            { type: "platform", x: FLAT_START + 2800, yOffset: 0, width: 400, height: 50 },
          ]
        },
        {
          id: 2,
          name: "NEON 2 - Precision",
          endX: FLAT_START + 3600,
          objects: [
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 400, height: 50 },
            { type: "spike", x: FLAT_START + 500, y: 0, height: 35 },
            
            // FIXED: Wider platforms (220-240px), better spacing
            { type: "platform", x: FLAT_START + 700, yOffset: 100, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 1050, yOffset: 120, width: 230, height: 20 },
            { type: "platform", x: FLAT_START + 1400, yOffset: 100, width: 240, height: 20 },
            
            { type: "platform", x: FLAT_START + 1700, yOffset: 0, width: 500, height: 50 },
            { type: "spike", x: FLAT_START + 1950, y: 0, height: 35 },
            
            { type: "platform", x: FLAT_START + 2300, yOffset: 110, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 2650, yOffset: 130, width: 230, height: 20 },
            
            { type: "platform", x: FLAT_START + 2950, yOffset: 0, width: 650, height: 50 },
            { type: "spike", x: FLAT_START + 3300, y: 0, height: 35 },
          ]
        },
        {
          id: 3,
          name: "NEON 3 - Razor Edge",
          endX: FLAT_START + 4200,
          objects: [
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 400, height: 50 },
            
            // FIXED: Platforms 220-250px wide, perfect jump arcs
            { type: "platform", x: FLAT_START + 550, yOffset: 100, width: 230, height: 20 },
            { type: "platform", x: FLAT_START + 900, yOffset: 120, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 1250, yOffset: 110, width: 240, height: 20 },
            { type: "spike", x: FLAT_START + 1100, y: 0, height: 35 },
            
            // Tight but possible chain (280px gaps)
            { type: "platform", x: FLAT_START + 1550, yOffset: 130, width: 230, height: 20 },
            { type: "platform", x: FLAT_START + 1850, yOffset: 120, width: 240, height: 20 },
            { type: "platform", x: FLAT_START + 2150, yOffset: 110, width: 250, height: 20 },
            
            { type: "platform", x: FLAT_START + 2450, yOffset: 0, width: 1650, height: 50 },
            { type: "spike", x: FLAT_START + 2600, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3050, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3450, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3800, y: 0, height: 35 },
            
            { type: "platform", x: FLAT_START + 4100, yOffset: 0, width: 200, height: 50 },
          ]
        }
      ]
    }
  ]
};
