
#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Os.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/graphics/drawable/shapes/COvalShape.h"

namespace Elastos {
namespace Droid {
namespace Graphics {
namespace Drawable {
namespace Shapes {

CAR_OBJECT_IMPL(COvalShape);
ECode COvalShape::constructor()
{
    return NOERROR;
}

ECode COvalShape::Clone(
    /* [out] */ IInterface** shape)
{
    VALIDATE_NOT_NULL(shape);
    AutoPtr<IRectShape> s;
    COvalShape::New((IRectShape**)&s);
    OvalShape::CloneImpl(s);
    *shape = s.Get();
    REFCOUNT_ADD(*shape);
    return NOERROR;
}

} // namespace Shapes
} // namespace Drawable
} // namespace Graphics
} // namespace Droid
} // namespace Elastos
