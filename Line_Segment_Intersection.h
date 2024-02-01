// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
inline int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
inline bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

inline bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

inline sf::Vector2f CalcIntersection(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2) {
	sf::Vector2f pInt;
	if (doIntersect(p1, q1, p2, q2)) {
		pInt.x = ((p1.x * q1.y - p1.y * q1.x) * (p2.x - q2.x) - (p2.x * q2.y - p2.y * q2.x) * (p1.x - q1.x)) / ((p1.x - q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x - q2.x));

		pInt.y = ((p1.x * q1.y - p1.y * q1.x) * (p2.y - q2.y) - (p2.x * q2.y - p2.y * q2.x) * (p1.y - q1.y)) / ((p1.x - q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x - q2.x));

	}
	return pInt;
}

/*
void renderEdge(Edge E, sf::RenderWindow& window) {
	using namespace std;

	sf::CircleShape circle(3);
	circle.setPosition(sf::Vector2f(E.p1.x, E.p1.y));
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setFillColor(sf::Color::Green);
	window.draw(circle);

	circle.setPosition(sf::Vector2f(E.p2.x, E.p2.y));
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setFillColor(sf::Color::Green);
	window.draw(circle);

	sf::RectangleShape rect(sf::Vector2f(2, distanceBetweenPoints(sf::Vector2f(E.p1.x, E.p1.y), sf::Vector2f(E.p2.x, E.p2.y))));
	rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
	float avgX = (E.p1.x + E.p2.x) / 2;
	float avgY = (E.p1.y + E.p2.y) / 2;
	float rotation = atan2(E.p1.y - E.p2.y, E.p1.x - E.p2.x);
	// converts radians to degrees
	rotation = rotation * 180 / 3.14159;
	rect.setPosition(avgX, avgY);
	rect.setRotation(rotation + 90);
	rect.setFillColor(sf::Color::Green);
	window.draw(rect);
}

void rotate_point(float cx, float cy, float angle, Point &p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Line Intersection Test");
	Point p1;
	p1.x = 100; p1.y = 0;
	Point p2;
	p2.x = 100; p2.y = 100;
	Point q1;
	q1.x = 70; q1.y = 30;
	Point q2;
	q2.x = 130; q2.y = 130;

	Edge E1;
	E1.p1 = p1;
	E1.p2 = p2;
	Edge E2;
	E2.p1 = q1;
	E2.p2 = q2;

	Point c1;
	c1.x = (p1.x + p2.x) / 2;
	c1.y = (p1.y + p2.y) / 2;
	Point c2;
	c2.x = (q1.x + q2.x) / 2;
	c2.y = (q1.y + q2.y) / 2;
	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		rotate_point(c1.x, c1.y, .002, E1.p1);
		rotate_point(c1.x, c1.y, .002, E1.p2);
		rotate_point(c2.x, c2.y, .001, E2.p1);
		rotate_point(c2.x, c2.y, .001, E2.p2);
		renderEdge(E1, window);
		renderEdge(E2, window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		Point pInt = CalcIntersection(E1.p1, E1.p2, E2.p1, E2.p2);
		sf::CircleShape circle;
		circle.setRadius(3);
		circle.setFillColor(sf::Color::Blue);
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		circle.setPosition(sf::Vector2f(pInt.x, pInt.y));
		window.draw(circle);
		window.display();
	}
	return 0;
};*/
