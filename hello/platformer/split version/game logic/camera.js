function updateCamera() {
  const viewWidth  = canvas.width  / cameraZoom;
  const viewHeight = canvas.height / cameraZoom;

  cameraX = player.x + player.w / 2 - viewWidth  / 2;
  cameraY = player.y + player.h / 2 - viewHeight / 2;

  if (cameraX < 0) cameraX = 0;
  if (cameraY < 0) cameraY = 0;
  if (cameraX > levelWidth  - viewWidth)  cameraX = levelWidth  - viewWidth;
  if (cameraY > levelHeight - viewHeight) cameraY = levelHeight - viewHeight;
}
