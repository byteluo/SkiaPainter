#ifndef   _ICANVAS_   
#define   _ICANVAS_   

#define Canvas ICanvas<double>

template<typename T>
class ICanvas
{
public:
	virtual void fillRect(T x, T y, T width, T height) = 0;
	virtual void strokeRect(T x, T y, T width, T height) = 0;
	virtual void clearRect(T x, T y, T width, T height) = 0;

	virtual void beginPath() = 0;
	virtual void closePath() = 0;
	virtual void stroke() = 0;
	virtual void fill() = 0;
	virtual void moveTo(T x, T y) = 0;
	virtual void lineTo(T x, T y) = 0;
	virtual void arc(T x, T y, T r, double startAngle, double endAngle, bool anticlockwise) = 0;
	virtual void arcTo(T x1, T y1, T x2, T y2, T radius) = 0;
	virtual void quadraticCurveTo(T cp1x, T cp1y, T x, T y) = 0;
	virtual void bezierCurveTo(T cp1x, T cp1y, T cp2x, T cp2y, T x, T y) = 0;
	virtual void rect(T x, T y, T width, T height) = 0;

	virtual void setStrokeStyle(const char* style) = 0;
	virtual const char* getStrokeStyle() = 0;
	virtual void setFillStyle(const char* style) = 0;
	virtual const char* getFillStyle() = 0;
	virtual void setLineWidth(T lineWidth) = 0;
	virtual T getLineWidth() = 0;
	virtual void setLineCap(const char* lineCap) = 0;
	virtual const char* getLineCap() = 0;
	virtual void setLineJoin(const char* lineJoin) = 0;
	virtual const char* getLineJoin() = 0;


	virtual void fillText(const char* text, T x, T y) = 0;
	virtual void strokeText(const char* text, T x, T y) = 0;
	virtual void setFont(const char* font) = 0;

	virtual void clip() = 0;

	virtual void save() = 0;
	virtual void restore() = 0;
	virtual void translate(T x, T y) = 0;
	virtual void rotate(double angle) = 0;
	virtual void scale(double x, double y) = 0;

	virtual void save2Image(const char* dest) = 0;

	virtual void setTransform(T a, T b, T c, T d, T e, T f) = 0;
};

#endif   