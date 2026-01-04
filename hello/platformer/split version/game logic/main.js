function loop() {
  if (mode === "game") {
    updateGame();
  } else {
    updateEditorFly();
  }
  updateCamera();
  drawWorldAndPlayer();

  if (mode === "editor") {
    if (activeMover) {
      editorInfo.textContent =
        "Mover selected | Dist: " + activeMover.pushDist +
        " | Glue: " + (gluePlacement ? "ON" : "OFF") +
        " | Controls: G glue, +/- distance, Esc clear.";
    } else if (activeRotator) {
      editorInfo.textContent =
        "Rotator selected | Glue: " + (gluePlacement ? "ON" : "OFF") +
        " | Controls: G glue, Esc clear.";
    } else {
      editorInfo.textContent =
        "Editor fly. Map " + currentMap().name +
        " | Avatar tile (" +
        Math.floor(player.x / tileSize) + ", " +
        Math.floor(player.y / tileSize) + ")";
    }
  }

  requestAnimationFrame(loop);
}

// Init maps and start
initMaps();
loop();
