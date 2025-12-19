// worldData.js — EXACT STEREO MADNESS RECREATION + SEQUELS
const FLAT_START = 600;

const GAME_DATA = {
  worlds: [
    {
      id: 1,
      name: "NEON",
      levels: [
        // === STEREO MADNESS (Exact replica) ===
        {
          id: 1,
          name: "STEREO MADNESS",
          endX: FLAT_START + 4500,
          objects: [
            // Long safe start (like GD)
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 5000, height: 50 },
            
            // Spike rhythm section (every 350px, perfect jump timing)
            { type: "spike", x: FLAT_START + 1400, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 1750, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 2100, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 2450, y: 0, height: 35 },
            
            // First jump-up (exact Stereo Madness pattern)
            { type: "platform", x: FLAT_START + 2800, yOffset: 100, width: 300, height: 20 },
            
            // Ground with spike breaks
            { type: "platform", x: FLAT_START + 3150, yOffset: 0, width: 1350, height: 50 },
            { type: "spike", x: FLAT_START + 3400, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3900, y: 0, height: 35 },
            
            // Safe finish
            { type: "platform", x: FLAT_START + 4300, yOffset: 0, width: 300, height: 50 }
          ]
        },

        // === BACK ON TRACK (platform chains + spikes) ===
        {
          id: 2,
          name: "BACK ON TRACK",
          endX: FLAT_START + 5200,
          objects: [
            // Safe start
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 1000, height: 50 },
            
            // 3-platform climb (exact Back on Track)
            { type: "platform", x: FLAT_START + 1200, yOffset: 100, width: 250, height: 20 },
            { type: "platform", x: FLAT_START + 1550, yOffset: 140, width: 250, height: 20 },
            { type: "platform", x: FLAT_START + 1900, yOffset: 100, width: 250, height: 20 },
            
            // Ground recovery + spikes
            { type: "platform", x: FLAT_START + 2200, yOffset: 0, width: 1800, height: 50 },
            { type: "spike", x: FLAT_START + 2500, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3000, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3500, y: 0, height: 35 },
            
            // Final safe zone
            { type: "platform", x: FLAT_START + 4800, yOffset: 0, width: 500, height: 50 }
          ]
        },

        // === POLARGEIST (tight air platforms) ===
        {
          id: 3,
          name: "POLARGEIST",
          endX: FLAT_START + 5800,
          objects: [
            // Safe start
            { type: "platform", x: 0, yOffset: 0, width: FLAT_START + 800, height: 50 },
            
            // Tight 5-platform chain (Polargeist signature)
            { type: "platform", x: FLAT_START + 1000, yOffset: 120, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 1350, yOffset: 140, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 1700, yOffset: 130, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 2050, yOffset: 150, width: 220, height: 20 },
            { type: "platform", x: FLAT_START + 2400, yOffset: 120, width: 250, height: 20 },
            
            // Spike corridor landing
            { type: "platform", x: FLAT_START + 2700, yOffset: 0, width: 3000, height: 50 },
            { type: "spike", x: FLAT_START + 2900, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3400, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 3900, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 4400, y: 0, height: 35 },
            { type: "spike", x: FLAT_START + 4900, y: 0, height: 35 },
            
            // Victory platform
            { type: "platform", x: FLAT_START + 5500, yOffset: 0, width: 400, height: 50 }
          ]
        }
      ]
    }
  ]
};
