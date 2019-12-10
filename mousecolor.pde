
//float hex3 = mouseX;

void setup (){
  size (500, 500);
  background (255);
  
}

void draw() {
  mousePressed();
}

 
  void mousePressed(){
    int hex1 = mouseX;
    int hex2 = mouseY;
    noStroke();
    fill(hex1, hex2, random(0,255));
    ellipse(mouseX, mouseY, 10, 10);
  

}
