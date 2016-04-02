//
//  UIImageView+YJCategory.h
//  YJKit
//
//  Created by huang-kun on 16/3/31.
//  Copyright © 2016年 huang-kun. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_OPTIONS(NSUInteger, YJViewContentMode) {
    // Alignment
    YJViewContentModeCenter             = 0 << 0,
    YJViewContentModeTop                = 1 << 0,
    YJViewContentModeLeft               = 1 << 1,
    YJViewContentModeBottom             = 1 << 2,
    YJViewContentModeRight              = 1 << 3,
    // Aspect Scaling
    YJViewContentModeScaleAspectFit     = 1 << 4,
    YJViewContentModeScaleAspectFill    = 2 << 4,
};

@interface UIImageView (YJCategory)

/**
 *  @brief The YJViewContentMode for replacing the default UIViewContentMode. Set yj_contentMode will ignore the contentMode property for image display.
 *  @discussion The yj_contentMode achieves the possibility of make combination image displaying result which is not provided by UIViewContentMode. e.g. set (ScaleAspectFit | Left) will display image as same as UIViewContentModeScaleAspectFit first, then align the scaled image as same as UIViewContentModeLeft under the first condition. You can get result of both ScaleAspectFit and Left.
 *  @remark The yj_contentMode can be set a combination of multiple values, like (ScaleAspectFit | Top | Left). However, sometimes not all values can be satisfied, like (ScaleAspectFit | ScaleAspectFill) or (Top | Bottom) or (Left | Center). When conflict appears, the values will get filtered by priorities. \n
 
 *  The priority of each value from high to low will be marked as follow:
 *  @code
 (ScaleAspectFit > ScaleAspectFill) > (Top > Left > Right > Bottom > Center).
 *  @endcode
 If any low priority value conflicts with high priority value, the lower one is ignored.  e.g. For (ScaleAspectFit | ScaleAspectFill) will keep ScaleAspectFit; (Left | Center) will keep Left; (Top | Left | Bottom) will keep (Top | Left).
 *
 */
@property (nonatomic) YJViewContentMode yj_contentMode;

@end
