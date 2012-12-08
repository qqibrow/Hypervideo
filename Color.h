#include <QColor>
#include <vector>


class ColorFactory
{
public:
	static std::vector<QColor> getListofColors();
protected:
private:
	ColorFactory();
};