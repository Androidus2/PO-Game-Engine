#include "ColorPicker.h"
#include "Game.h"
#include "Utility.h"

using namespace std;
using namespace sf;


void ColorPicker::drawHSV(Vertex& point, double h, double s, double v, double alpha) {
    // Pick the correct case based on our position on the color wheel.
    const int cs = h * 6;

    // Calculate some helper values used in our cases below.
    const double f = h * 6 - cs;
    const double p = v * (1 - s);
    const double q = v * (1 - s * f);
    const double t = v * (1 - s * (1 - f));

    switch (cs) {
    case 0:
    case 6:
        point.color = Color(v * 255, t * 255, p * 255, 255 * alpha);
        break;
    case 1:
        point.color = Color(q * 255, v * 255, p * 255, 255 * alpha);
        break;
    case 2:
        point.color = Color(p * 255, v * 255, t * 255, 255 * alpha);
        break;
    case 3:
        point.color = Color(p * 255, q * 255, v * 255, 255 * alpha);
        break;
    case 4:
        point.color = Color(t * 255, p * 255, v * 255, 255 * alpha);
        break;
    case 5:
        point.color = Color(v * 255, p * 255, q * 255, 255 * alpha);
        break;
    }
}
void ColorPicker::modulate(VertexArray& points, double hue) {
    // First, Let's "sanitize" inputs a bit.
    // Don't accept negative numbers.
    if (hue < 0)
        hue = 0;
    // Lazy overflow by subtracting the integer portion of the number.
    else if (hue > 1)
        hue -= static_cast<int>(hue);

    // Now iterate over all "pixels" and upate their colors.
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            // "Calculate" our missing HSV components with ranges from 0 to 1.
            const double s = x / 255.; // x is our saturation
            const double v = y / 255.; // y is our value

            // Draw the pixel.
            drawHSV(points[y * 256 + x], hue, s, v, 1);
        }
    }
}
void ColorPicker::accuratePosition(int& x, int& y, int xLimit, int yLimit) {
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x > xLimit)
        x = xLimit;
    if (y > yLimit)
        y = yLimit;
}
void ColorPicker::setCursorsBasedOnColor() {
    double r = selectedColor.r / 255.;
    double g = selectedColor.g / 255.;
    double b = selectedColor.b / 255.;
    double maxx = max(r, max(g, b));
    double minn = min(r, min(g, b));
    double delta = maxx - minn;
    double h = 0;
    if (delta == 0)
        h = 0;
    else if (maxx == r)
        h = 60 * fmod((g - b) / delta, 6);
    else if (maxx == g)
        h = 60 * ((b - r) / delta + 2);
    else
        h = 60 * ((r - g) / delta + 4);
    if (h < 0)
        h += 360;
    double s = maxx == 0 ? 0 : delta / maxx;
    double v = maxx;
    double a = selectedColor.a / 255.;

    colorsOffset = Vector2f(255 * s, 255 * v);
    hueBarOffset = Vector2f(hueBarOffset.x, h * 255 / 360);
    alphaBarOffset = Vector2f(alphaBarOffset.x, a * 255);

    modulate(colorsDisplay, h / 360);

    reposition();
}
void ColorPicker::reposition() {
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            Vertex& vertex(colorsDisplay[y * 256 + x]);
            vertex.position.x = 255 - x + position.x + 5;
            vertex.position.y = 255 - y + position.y + 30;
        }
    }

    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x < 20; ++x) {
            Vertex& vertex(hueBarDisplay[y * 20 + x]);
            vertex.position.x = x + position.x + size.x - 55;
            vertex.position.y = y + position.y + 30;

            // Calculate the hue value based on the y position.
            const double hue = y / 255.;
            drawHSV(vertex, hue, 1, 1, 1);
        }
    }

    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x < 20; ++x) {
            Vertex& vertex(alphaBarDisplay[y * 20 + x]);
            vertex.position.x = x + position.x + size.x - 25;
            vertex.position.y = y + position.y + 30;

            // Calculate the hue value based on the y position.
            drawHSV(vertex, 1, 0, y / 255., y / 255.);
        }
    }

    alphaBarBackground.setPosition(position.x + size.x - 25, position.y + 29);

    colorsCursor.setPosition(colorsDisplay[colorsOffset.y * 256 + colorsOffset.x].position);
    hueBarCursor.setPosition(hueBarDisplay[hueBarOffset.y * 20 + hueBarOffset.x].position);
    alphaBarCursor.setPosition(alphaBarDisplay[alphaBarOffset.y * 20 + alphaBarOffset.x].position);
}
ColorPicker::ColorPicker(Font& font, const Vector2f& position, const Vector2f& size, const string& title) : EditorWindow(font, position, size, title) {
    colorsDisplay = VertexArray(Points, 256 * 256);
    hueBarDisplay = VertexArray(Points, 256 * 20);
    alphaBarDisplay = VertexArray(Points, 256 * 20);

    colorsOffset = Vector2f(0, 255);
    hueBarOffset = Vector2f(0, 0);
    alphaBarOffset = Vector2f(19, 255);

    colorsCursor = CircleShape(5);
    colorsCursor.setOrigin(5, 5);
    colorsCursor.setFillColor(Color::Transparent);
    colorsCursor.setOutlineColor(Color::Black);
    colorsCursor.setOutlineThickness(2);

    hueBarCursor = CircleShape(5);
    hueBarCursor.setOrigin(5, 5);
    hueBarCursor.setFillColor(Color::Transparent);
    hueBarCursor.setOutlineColor(Color::Black);
    hueBarCursor.setOutlineThickness(2);

    alphaBarCursor = CircleShape(5);
    alphaBarCursor.setOrigin(5, 5);
    alphaBarCursor.setFillColor(Color::Transparent);
    alphaBarCursor.setOutlineColor(Color::Red);
    alphaBarCursor.setOutlineThickness(2);

    alphaBarBackground = RectangleShape(Vector2f(20, 256));
    alphaBarBackground.setFillColor(Color::Black);
    alphaBarBackground.setOutlineColor(Color::White);
    alphaBarBackground.setOutlineThickness(1);
    alphaBarBackground.setPosition(position.x + size.x - 25, position.y + 29);

    reposition();

    modulate(colorsDisplay, 0);

    Text* tmp = new Text("Color: ", font, 15);
    tmp->setPosition(position.x + 15, position.y + 295);
    texts.push_back(*tmp);
    delete tmp;

    InputField* tmp2 = new InputField(font, Vector2f(position.x + 70, position.y + 295), Vector2f(100, 20), "#00000000");
    tmp2->setOnlyNumbers(false);
    inputFields.push_back(*tmp2);
    delete tmp2;


    selectedColor = Color::White;
    selected = -1;
    isActive = false;
    isDragglable = true;

    topBar.setSize(Vector2f(0, 0));
    bottomBar.setSize(Vector2f(0, 0));
}
void ColorPicker::handleEvent(Event& event) { //handle event function
    if (!isActive)
        return;
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
        if (colorsDisplay.getBounds().contains(mousePos))
            selected = 0;
        else if (hueBarDisplay.getBounds().contains(mousePos))
            selected = 1;
        else if (alphaBarDisplay.getBounds().contains(mousePos))
            selected = 2;
        else if (!window.getGlobalBounds().contains(mousePos))
            setActive(false);
    }
    else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
        selected = -1;
    EditorWindow::handleEvent(event);
}
void ColorPicker::draw(RenderWindow& window) const { //draw function
    if (!isActive)
        return;
    EditorWindow::draw(window);
    window.draw(colorsDisplay);
    window.draw(hueBarDisplay);
    window.draw(alphaBarBackground);
    window.draw(alphaBarDisplay);
    window.draw(colorsCursor);
    window.draw(hueBarCursor);
    window.draw(alphaBarCursor);
}
void ColorPicker::update() { //update function
    if (!isActive)
        return;
    EditorWindow::update();
    if (selected == -1) {
        if (!inputFields[0].getSelected())
            inputFields[0].setText("#" + ColorToString(selectedColor));
        else {
            selectedColor = stringToColor(inputFields[0].getText());
            setCursorsBasedOnColor();
        }
    }
}
void ColorPicker::mouseOver() { //mouse over function (used to check if the mouse is over the color picker window and to check the color picker's elements)
    if (!isActive)
        return;
    Vector2f mousePos = Vector2f(Mouse::getPosition(*Game::getWindow()).x, Mouse::getPosition(*Game::getWindow()).y);
    if (selected == 0) {
        int relativeX = 255 - (mousePos.x - colorsDisplay[255].position.x);
        int relativeY = 255 - (mousePos.y - colorsDisplay[255 * 256 - 1].position.y);
        accuratePosition(relativeX, relativeY, 255, 255);
        colorsCursor.setPosition(255 - relativeX + colorsDisplay[255].position.x, 255 - relativeY + colorsDisplay[255 * 256 - 1].position.y);
        selectedColor = colorsDisplay[relativeY * 256 + relativeX].color;
        selectedColor.a = alphaBarDisplay[alphaBarOffset.y * 20 + alphaBarOffset.x].color.a;
        colorsOffset = Vector2f(relativeX, relativeY);
    }
    else if (selected == 1) {
        int relativeY = mousePos.y - hueBarDisplay[0].position.y;
        int relativeX = mousePos.x - hueBarDisplay[0].position.x;
        accuratePosition(relativeX, relativeY, 19, 255);
        hueBarCursor.setPosition(relativeX + hueBarDisplay[0].position.x, relativeY + hueBarDisplay[0].position.y);
        modulate(colorsDisplay, relativeY / 255.);
        hueBarOffset = Vector2f(relativeX, relativeY);
        relativeX = 255 - (colorsCursor.getPosition().x - colorsDisplay[255].position.x);
        int relativeY2 = 255 - (colorsCursor.getPosition().y - colorsDisplay[255 * 256 - 1].position.y);
        accuratePosition(relativeX, relativeY2, 255, 255);
        selectedColor = colorsDisplay[relativeY2 * 256 + relativeX].color;
        selectedColor.a = alphaBarDisplay[alphaBarOffset.y * 20 + alphaBarOffset.x].color.a;
    }
    else if (selected == 2) {
        int relativeX = mousePos.x - alphaBarDisplay[0].position.x;
        int relativeY = mousePos.y - alphaBarDisplay[0].position.y;
        accuratePosition(relativeX, relativeY, 19, 255);
        alphaBarCursor.setPosition(relativeX + alphaBarDisplay[0].position.x, relativeY + alphaBarDisplay[0].position.y);
        selectedColor.a = alphaBarDisplay[relativeY * 20 + relativeX].color.a;
        alphaBarOffset = Vector2f(relativeX, relativeY);
    }
    if (!inputFields[0].getSelected())
        inputFields[0].setText("#" + ColorToString(selectedColor));
    for (int i = 0; i < inputFields.size(); i++) {
        inputFields[i].checkMouseClick();
    }
}
void ColorPicker::drag(Event& event) {
    EditorWindow::drag(event);
    if (isDragging) {
        reposition();
    }

}
Color ColorPicker::getSelectedColor() const { //get the selected color of the color picker
    return selectedColor;
}
void ColorPicker::setSelectedColor(const Color& color) { //set the selected color of the color picker
    selectedColor = color;
    setCursorsBasedOnColor();
}
void ColorPicker::setActive(bool active) { //set the active state of the color picker
    isActive = active;
    selected = -1;
    if (!active) {
        inputFields[0].deselect();
        inputFields[0].setText("#" + ColorToString(selectedColor));
    }
}
ColorPicker::~ColorPicker() {} //destructor
