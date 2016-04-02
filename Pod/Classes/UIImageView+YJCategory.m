//
//  UIImageView+YJCategory.m
//  YJKit
//
//  Created by huang-kun on 16/3/31.
//  Copyright © 2016年 huang-kun. All rights reserved.
//

#import <objc/runtime.h>
#import "UIImageView+YJCategory.h"
#import "CGGeometry_YJExtension.h"

@interface UIImageView ()
@property (nonatomic) BOOL yj_contentModeEnabled;
@end

@implementation UIImageView (YJCategory)

+ (void)load {
    SEL fromSelector = @selector(setImage:);
    SEL toSelector = @selector(_yj_setImage:);
    
    Class class = [self class];
    
    Method fromMethod = class_getInstanceMethod(class, fromSelector);
    Method toMethod = class_getInstanceMethod(class, toSelector);
    
    BOOL added = class_addMethod(class, fromSelector, method_getImplementation(toMethod), method_getTypeEncoding(toMethod));
    if (added) class_replaceMethod(class, toSelector, method_getImplementation(fromMethod), method_getTypeEncoding(fromMethod));
    else method_exchangeImplementations(fromMethod, toMethod);
}

#pragma mark - yj_contentMode

- (void)setYj_contentModeEnabled:(BOOL)yj_contentModeEnabled {
    objc_setAssociatedObject(self, @selector(yj_contentModeEnabled), @(yj_contentModeEnabled), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (BOOL)yj_contentModeEnabled {
    return [objc_getAssociatedObject(self, _cmd) boolValue];
}

- (void)setYj_contentMode:(YJViewContentMode)yj_contentMode {
    self.yj_contentModeEnabled = YES;
    objc_setAssociatedObject(self, @selector(yj_contentMode), @(yj_contentMode), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (YJViewContentMode)yj_contentMode {
    return [objc_getAssociatedObject(self, _cmd) unsignedIntegerValue];
}

#pragma mark - set image

- (void)_yj_setImage:(UIImage *)image {
    if (!self.yj_contentModeEnabled) {
        [self _yj_setImage:image];
        return;
    }
    CGSize contextSize = self.bounds.size;
    CGRect imageRect = (CGRect){ CGPointZero, image.size };
    CGRect targetRect = (CGRect){ CGPointZero, contextSize };
    targetRect = CGRectPositioned(imageRect, targetRect, self.yj_contentMode);
    UIGraphicsBeginImageContextWithOptions(contextSize, NO, image.scale);
    [image drawInRect:targetRect];
    UIImage *resizedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    [self _yj_setImage:resizedImage];
}

@end
