//
//  CGGeometry_YJExtension.h
//  YJKit
//
//  Created by huang-kun on 16/3/24.
//  Copyright © 2016年 huang-kun. All rights reserved.
//

#ifndef CGGeometry_YJExtension_h
#define CGGeometry_YJExtension_h

#include <CoreGraphics/CGGeometry.h>

typedef enum {
    CGSizeScaleNone         = 0x00,
    CGSizeScaleAspectFit    = 0x10,
    CGSizeScaleAspectFill   = 0x20,
} CGSizeScaleRule;

typedef enum {
    CGRectScaleNone         = CGSizeScaleNone,
    CGRectScaleAspectFit    = CGSizeScaleAspectFit,
    CGRectScaleAspectFill   = CGSizeScaleAspectFill,
} CGRectScaleRule;

typedef enum {
    CGRectAlignCenter       = 0x00,
    CGRectAlignTop          = 0x01,
    CGRectAlignLeft         = 0x02,
    CGRectAlignBottom       = 0x04,
    CGRectAlignRight        = 0x08,
    
    CGRectAlignTopLeft      = 0x03,
    CGRectAlignTopRight     = 0x09,
    CGRectAlignBottomLeft   = 0x06,
    CGRectAlignBottomRight  = 0x0C,
} CGRectAlignRule;

/**
 *  CGRectPositionOptions is considered as an enum type which contains the CGRectScaleRule and CGRectAlignRule.
 *  @code
 enum CGRectPositionOptions {
     // CGRectAlignRule
     CGRectAlignCenter     = 0 << 0,
     CGRectAlignTop        = 1 << 0,
     CGRectAlignLeft       = 1 << 1,
     CGRectAlignBottom     = 1 << 2,
     CGRectAlignRight      = 1 << 3,
     
     // CGRectScaleRule
     CGRectScaleNone       = 0 << 4,
     CGRectScaleAspectFit  = 1 << 4,
     CGRectScaleAspectFill = 2 << 4,
 };
 *  @endcode
 */
typedef unsigned int CGRectPositionOptions;

/// Returns a rect which has the same top edge position as "sameWithRect" parameter.
CG_INLINE CGRect CGRectSetEqualTopToRect(CGRect rect, CGRect sameWithRect) {
    rect.origin.y = sameWithRect.origin.y;
    return rect;
}

/// Returns a rect which has the same left edge position as "sameWithRect" parameter.
CG_INLINE CGRect CGRectSetEqualLeftToRect(CGRect rect, CGRect sameWithRect) {
    rect.origin.x = sameWithRect.origin.x;
    return rect;
}

/// Returns a rect which has the same bottom edge position as "sameWithRect" parameter.
CG_INLINE CGRect CGRectSetEqualBottomToRect(CGRect rect, CGRect sameWithRect) {
    rect.origin.y = sameWithRect.origin.y + sameWithRect.size.height - rect.size.height;
    return rect;
}

/// Returns a rect which has the same right edge position as "sameWithRect" parameter.
CG_INLINE CGRect CGRectSetEqualRightToRect(CGRect rect, CGRect sameWithRect) {
    rect.origin.x = sameWithRect.origin.x + sameWithRect.size.width - rect.size.width;
    return rect;
}

/// Returns a rect which has the same center position as "sameWithRect" parameter.
CG_INLINE CGRect CGRectSetEqualCenterToRect(CGRect rect, CGRect sameWithRect) {
    rect.origin.x = sameWithRect.origin.x + sameWithRect.size.width / 2 - rect.size.width / 2;
    rect.origin.y = sameWithRect.origin.y + sameWithRect.size.height / 2 - rect.size.height / 2;
    return rect;
}

/**
 *  @brief Calculate a size that fits or fills in the target size.
 *
 *  @param originalSize  The size needs to be resized.
 *  @param inSize        The target size for originalSize to fit or fill into.
 *  @param scaleRule     The option for scaling. Passing 0 will not trigger any resizing effect.
 *
 *  @return Returns a new size that fits or fills in the target size.
 */
CGSize CGSizeScaleToSize(CGSize originalSize, CGSize inSize, CGSizeScaleRule scaleRule);

/**
 *  @brief Calculate a rect that positions in the target rect.
 *
 *  @discussion e.g. If you apply CGRectScaleAspectFit as scaleRule and CGRectAlignTop as alignRule, the result will satisfy both situations. It will satisfy the CGRectScaleAspectFit by making the rect to fit in the terget rect as first duty, then it will achieve the CGRectAlignTop by placing the resized rect as same top of the target rect. So achieving the alignRule is always under the condition of satisfying the scaleRule.
 *
 *  @code
 CGRect newRect = CGRectPositionToRect(originalRect, targetRect, CGRectScaleAspectFit, CGRectAlignTop);
 *  @endcode
 *
 *  @param originalRect  The rect needs to be resized and re-positioned.
 *  @param inRect        The target rect for originalRect to fit or fill into.
 *  @param scaleRule     The option for scaling. Passing 0 will not trigger any resizing effect.
 *  @param alignRule     The options for the alignment. Passing 0 will set CGRectAlignCenter.
 *
 *  @return Returns a rect that positions in the target rect.
 */
CGRect CGRectPositionToRect(CGRect originalRect, CGRect inRect, CGRectScaleRule scaleRule, CGRectAlignRule alignRule);

/**
 *  @brief Calculate a rect that positions in the target rect.
 *
 *  @discussion e.g. If you apply (CGRectScaleAspectFit | CGRectAlignTop) as positionOptions, the result will satisfy both situations. It will satisfy the CGRectScaleAspectFit by making the rect to fit in the terget rect as first duty, then it will achieve the CGRectAlignTop by placing the resized rect as same top of the target rect. So achieving the alignRule is always under the condition of satisfying the scaleRule.
 *
 *  @remark The positionOptions can be set a combination of multiple values, like (ScaleAspectFit | AlignTop | AligLeft). However, sometimes not all values can be satisfied, like (ScaleAspectFit | ScaleAspectFill) or (AlignTop | AlignBottom) or (AlignLeft | AlignCenter). When conflict appears, the values will get filtered by priorities. \n
 
 *  The priority of each value from high to low will be marked as follow: 
 *  @code
 (ScaleAspectFit > ScaleAspectFill) > (Top > Left > Right > Bottom > Center). 
 *  @endcode
 If any low priority value conflicts with high priority value, the lower one is ignored.  e.g. For (ScaleAspectFit | ScaleAspectFill) will keep ScaleAspectFit; (AlignLeft | AlignCenter) will keep AlignLeft; (AlignTop | AlignLeft | AlignBottom) will keep (AlignTop | AlignLeft).
 *
 *  The correct way to call the function:
 *  @code
 CGRect resizedFrame = CGRectPositioned(originalFrame, targetFrame, CGRectScaleAspectFit | CGRectAlignTop | CGRectAligLeft)
 *  @endcode
 *
 *  @param originalRect    The rect needs to be resized and re-positioned.
 *  @param inRect          The target rect for originalRect to fit or fill into.
 *  @param positionOptions The options for the scaling and alignment. Passing 0 will set CGRectAlignCenter.
 *
 *  @return Returns a rect that positions in the target rect.
 */
CGRect CGRectPositioned(CGRect originalRect, CGRect inRect, CGRectPositionOptions positionOptions);

#endif /* CGGeometry_YJExtension_h */
