#ifndef   _SKIA_CANVAS_   
#define   _SKIA_CANVAS_   
#include <iostream>

// Skia
#include <include/core/SkCanvas.h>
#include <include/core/SkPaint.h>
#include <include/core/SkPath.h>
#include <include/core/SkShader.h>
#include <include/core/SkTypeface.h>
#include <include/core/SkTypes.h>
#include <include/core/SkFont.h>
#include <include/core/SkFontStyle.h>
#include <include/core/SkFontTypes.h>
#include <include/core/SkSurface.h>
#include <d3d12.h>
#pragma comment(lib, "D3D12.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "skia.lib")
#include <include/utils/SkParse.h>


const double PI = acos(-1);

using namespace std;

template<typename T>
class SkiaCanvas : public ICanvas<T> {
private:
	int width, height;
	SkBitmap* bitmap;
	SkCanvas* canvas;
	SkPaint paint;
	SkPaint fillPaint;
	SkPaint strokePaint;
	SkFont font;
	SkPath path;

	SkiaCanvas() {}

public:


	SkiaCanvas(SkCanvas* canvas) {
		fillPaint.setStyle(SkPaint::kFill_Style);
		fillPaint.setAntiAlias(true);
		strokePaint.setStyle(SkPaint::kStroke_Style);
		strokePaint.setAntiAlias(true);
		strokePaint.setStrokeWidth(2);
		canvas->clear(SK_ColorWHITE);
		font.setTypeface(SkTypeface::MakeFromName("simsun", SkFontStyle::Normal()));


		this->canvas = canvas;
		canvas->clear(SK_ColorWHITE);
	}

	SkiaCanvas(int w, int h) {
		width = w > 0 ? w : 500;
		height = h > 0 ? h : 500;
		
		fillPaint.setStyle(SkPaint::kFill_Style);
		fillPaint.setAntiAlias(true);
		strokePaint.setStyle(SkPaint::kStroke_Style);
		strokePaint.setAntiAlias(true);
		strokePaint.setStrokeWidth(1);
		font.setTypeface(SkTypeface::MakeFromName("simsun", SkFontStyle::Normal()));


		SkImageInfo imageInfo = SkImageInfo::Make(width, height, kBGRA_8888_SkColorType, kPremul_SkAlphaType);
		bitmap = new SkBitmap();
		bitmap->allocPixels(imageInfo, imageInfo.minRowBytes());
		canvas = new SkCanvas(*bitmap);
		canvas->clear(SK_ColorWHITE);

	}

	~SkiaCanvas() {
		cout << "SkiaCanvas Îö¹¹º¯Êý";
		delete canvas;
		delete bitmap;
	}


	void strokeText(const char* str, double x, double y) {
		canvas->drawSimpleText(str, strlen(str), SkTextEncoding::kUTF8, x, y, font, strokePaint);
	}

	void fillText(const char* str, double x, double y) {
		canvas->drawSimpleText(str, strlen(str), SkTextEncoding::kUTF8, x, y, font, fillPaint);
	}

	void save2Image(const char* dest) {
		SkFILEWStream stream(dest);
		SkEncodeImage(&stream, *bitmap, SkEncodedImageFormat::kPNG, 100);
	}

	void moveTo(T x, T y) {
		path.moveTo(x, y);
	}

	void lineTo(T x, T y) {
		path.lineTo(x, y);
	}

	void stroke() {
		canvas->drawPath(path, strokePaint);
	}

	void fill() {
		canvas->drawPath(path, fillPaint);
	}

	void dispose() {
		canvas->clear(SK_ColorWHITE);
	}

	void rotate(T radian) {
		canvas->rotate(radian / PI * 180);
	}

	void scale(double x, double y) {
		canvas->scale(x, y);
	}

	void translate(double x, double y) {
		canvas->translate(x, y);
	}

	void arc(T x, T y, T r, double startAngle, double endAngle, bool anticlockwise) {

		SkRect rect = SkRect::MakeXYWH(x - r, y - r, 2 * r, 2 * r);
		while (endAngle + 2 * PI <= 2 * PI) {
			endAngle += 2 * PI;
		}
		while (endAngle - 2 * PI > 0) {
			endAngle -= 2 * PI;
		}
		while (startAngle < 0) {
			startAngle += 2 * PI;
		}
		while (startAngle - 2 * PI >= 0) {
			startAngle -= 2 * PI;
		}

		double delta = 0;
		if (endAngle > startAngle) {
			if (!anticlockwise) {
				delta = endAngle - startAngle;
			}
			else {
				delta = -(2 * PI - (endAngle - startAngle));
			}
		}
		else {
			if (anticlockwise) {
				delta = -(startAngle - endAngle);
			}
			else {
				delta = 2 * PI - (startAngle - endAngle);
			}
		}
		
		path.addArc(rect, startAngle / PI * 180, delta / PI * 180);
	};

	void arcTo(T x1, T y1, T x2, T y2, T radius) {

	};
	void quadraticCurveTo(T cp1x, T cp1y, T x, T y) {
		SkPoint points[3];
		points[0].fX = cp1x;
		points[0].fY = cp1y;
		points[1].fX = x;
		points[1].fY = y;

		path.conicTo(points[0], points[1], 1);
	};
	void bezierCurveTo(T cp1x, T cp1y, T cp2x, T cp2y, T x, T y) {
		SkPoint points[3];
		points[0].fX = cp1x;
		points[0].fY = cp1y;
		points[1].fX = cp2x;
		points[1].fY = cp2y;
		points[2].fX = x;
		points[2].fY = y;

		path.cubicTo(points[0], points[1], points[2]);
	}

	void rect(T x, T y, T width, T height) {
		path.addRect(SkRect::MakeXYWH(x, y, width, height));
	}

	void strokeRect(double x1, double y1, double x2, double y2) {
		canvas->drawRect(SkRect::MakeXYWH(x1, y1, x2, y2), strokePaint);
	}

	void fillRect(T x1, T y1, T x2, T y2) {
		canvas->drawRect(SkRect::MakeXYWH(x1, y1, x2, y2), fillPaint);
	}

	void clearRect(T x1, T y1, T x2, T y2) {

	}

	void arc(double x, double y, double r) {

	}

	void closePath() {
		path.close();
	}

	void beginPath() {
		path.reset();
	}

	void setLineWidth(T w) {
		strokePaint.setStrokeWidth(w);
	}

	void setStrokeStyle(const char* style) {
		SkColor color = fillPaint.getColor();
		SkParse::FindColor(style, &color);
		strokePaint.setColor(color);
	}

	const char* getStrokeStyle() {
		return "";
	}
	const char* result;

	void setFillStyle(const char* style) {
		SkColor color = fillPaint.getColor();
		result = SkParse::FindColor(style, &color);
		fillPaint.setColor(color);
	}

	const char* getFillStyle() {
		return "";
	}

	T getLineWidth() {
		return 0;
	}
	void setLineCap(const char* lineCap) {

	}

	const char* getLineCap() {
		return "";
	}

	void setLineJoin(const char* lineJoin) {

	}
	const char* getLineJoin() {
		return "";
	}

	void save() {
		canvas->save();
	}

	void restore() {
		canvas->restore();
	}

	void setFont(const char* font) {
		SkScalar* scalar = new SkScalar();
		SkParse::FindScalar(font, scalar);
		this->font.setSize(*scalar);
		delete scalar;
	}

	void clip() {
		canvas->clipPath(path, true);
	}

	void setTransform(T a, T b, T c, T d, T e, T f) {
		auto m = SkMatrix::MakeAll(a, c, e, b, d, f, 0, 0, 1);
		canvas->setMatrix(m);
	}
};


#endif   