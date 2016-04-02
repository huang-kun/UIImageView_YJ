//
//  CGGeometry_YJExtension.c
//  YJKit
//
//  Created by huang-kun on 16/3/24.
//  Copyright © 2016年 huang-kun. All rights reserved.
//

#include "CGGeometry_YJExtension.h"

CGSize CGSizeScaleToSize(CGSize originalSize, CGSize inSize, CGSizeScaleRule scaleRule) {
    // Validation
    if (CGSizeEqualToSize(CGSizeZero, originalSize) && CGSizeEqualToSize(CGSizeZero, inSize))
        return CGSizeZero;
    else if (CGSizeEqualToSize(CGSizeZero, originalSize))
        return inSize;
    else if (CGSizeEqualToSize(CGSizeZero, inSize))
        return originalSize;
    // Set equal width
    CGSize finalSize = originalSize;
    CGFloat ratio = originalSize.width / originalSize.height;
    finalSize.width = inSize.width;
    finalSize.height = inSize.width / ratio;
    // Set equal height if needed
    switch (scaleRule) {
        case CGRectScaleNone:
            return originalSize;
        case CGRectScaleAspectFit:
            if (finalSize.height > inSize.height) goto _yj_setEqualHeight_; break;
        case CGRectScaleAspectFill:
            if (finalSize.height < inSize.height) goto _yj_setEqualHeight_; break;
    }
    return finalSize;
    
_yj_setEqualHeight_:
    finalSize.height = inSize.height;
    finalSize.width = inSize.height * ratio;
    return finalSize;
}

CGRect CGRectPositionToRect(CGRect originalRect, CGRect inRect, CGRectScaleRule scaleRule, CGRectAlignRule alignRule) {
    CGSize originalSize = originalRect.size;
    CGSize newSize = CGSizeScaleToSize(originalSize, inRect.size, (CGRectPositionOptions)scaleRule);
    CGPoint center = CGPointMake(CGRectGetMidX(inRect), CGRectGetMidY(inRect));
    CGPoint newOrigin = CGPointMake(center.x - newSize.width / 2, center.y - newSize.height / 2);
    CGRect r = (CGRect) { newOrigin, newSize };
    // If multiple values are applied, some of them may not be satisfied and result will be filtered by priority.
    // The priorites (from high to low) are: top -> left -> right -> bottom -> center
    if (alignRule & CGRectAlignBottom) r = CGRectSetEqualBottomToRect(r, inRect);
    if (alignRule & CGRectAlignRight) r = CGRectSetEqualRightToRect(r, inRect);
    if (alignRule & CGRectAlignLeft) r = CGRectSetEqualLeftToRect(r, inRect);
    if (alignRule & CGRectAlignTop) r = CGRectSetEqualTopToRect(r, inRect);
    return r;
}

CGRect CGRectPositioned(CGRect originalRect, CGRect inRect, CGRectPositionOptions positionOptions) {
    CGRectPositionOptions scaleOption = CGRectScaleNone;
    CGRectPositionOptions alignRule = positionOptions;
    // If "Fit" and "Fill" are both chosen, then "Fit" takes priority
    if (positionOptions & CGRectScaleAspectFill) {
        scaleOption = CGRectScaleAspectFill;
        alignRule = positionOptions ^ CGRectScaleAspectFill;
    }
    if (positionOptions & CGRectScaleAspectFit) {
        scaleOption = CGRectScaleAspectFit;
        alignRule = alignRule ^ CGRectScaleAspectFit;
    }
    return CGRectPositionToRect(originalRect, inRect, scaleOption, alignRule);
}
