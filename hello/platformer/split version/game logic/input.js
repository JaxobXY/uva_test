function pressButton(btn, key) {
  function handleDown() {
    if (key === 'zoomIn') {
      if (mode === "game") {
        cameraZoom += 0.1;
        if (cameraZoom > maxZoom) cameraZoom = maxZoom;
      }
    } else if (key === 'zoomOut') {
      if (mode === "game") {
        cameraZoom -= 0.1;
        if (cameraZoom < minZoom) cameraZoom = minZoom;
      }
    } else {
      input[key] = true;
    }
  }
  function handleUp() {
    if (key in input) input[key] = false;
  }

  btn.addEventListener('mousedown', handleDown);
  btn.addEventListener('mouseup', handleUp);
  btn.addEventListener('mouseleave', handleUp);

  btn.addEventListener('touchstart', e => {
    e.preventDefault();
    handleDown();
  }, { passive: false });
  btn.addEventListener('touchend', e => {
    e.preventDefault();
    handleUp();
  }, { passive: false });
  btn.addEventListener('touchcancel', e => {
    e.preventDefault();
    handleUp();
  }, { passive: false });
}

// D‑pad / mobile buttons
pressButton(leftBtn,   'left');
pressButton(rightBtn,  'right');
pressButton(upBtn,     'jump');
pressButton(downBtn,   'down');
pressButton(zoomInBtn, 'zoomIn');
pressButton(zoomOutBtn,'zoomOut');

// Hotbar
hotButtons.forEach(btn => {
  btn.addEventListener('click', () => {
    currentTileType = btn.getAttribute('data-tile');
    hotButtons.forEach(b => b.style.outline = "none");
    btn.style.outline = "2px solid #fff";
  });
});
hotButtons.forEach(b => {
  if (b.getAttribute('data-tile') === '#') {
    b.style.outline = "2px solid #fff";
  }
});

// Keyboard
addEventListener('keydown', e => {
  if (e.code === 'ArrowLeft' || e.code === 'KeyA')  input.left  = true;
  if (e.code === 'ArrowRight'|| e.code === 'KeyD')  input.right = true;
  if (e.code === 'ArrowDown' || e.code === 'KeyS')  input.down  = true;
  if (e.code === 'Space' || e.code === 'ArrowUp' || e.code === 'KeyW') input.jump = true;

  if (mode === "game") {
    if (e.code === 'KeyQ') {
      cameraZoom += 0.1;
      if (cameraZoom > maxZoom) cameraZoom = maxZoom;
    }
    if (e.code === 'KeyE') {
      cameraZoom -= 0.1;
      if (cameraZoom < minZoom) cameraZoom = minZoom;
    }
  }

  if (mode === "editor") {
    if (e.code === 'KeyG') {
      gluePlacement = !gluePlacement;
    } else if (e.key === '+') {
      if (activeMover) activeMover.pushDist += 10;
    } else if (e.key === '-') {
      if (activeMover) activeMover.pushDist = Math.max(10, activeMover.pushDist - 10);
    } else if (e.key === 'Escape') {
      activeMover = null;
      activeRotator = null;
      gluePlacement = false;
    }
  }
});

addEventListener('keyup', e => {
  if (e.code === 'ArrowLeft' || e.code === 'KeyA')  input.left  = false;
  if (e.code === 'ArrowRight'|| e.code === 'KeyD')  input.right = false;
  if (e.code === 'ArrowDown' || e.code === 'KeyS')  input.down  = false;
  if (e.code === 'Space' || e.code === 'ArrowUp' || e.code === 'KeyW') input.jump = false;
});
