#pragma once
#include <memory>

namespace rbe {
    class CDrawable {
    public:
        virtual ~CDrawable() {};
        virtual void Draw(int x, int y) = 0;
    };

    using CDrawablePtr = std::shared_ptr<CDrawable>;
}