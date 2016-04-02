//
//  YJViewController.m
//  UIImageView_YJ
//
//  Created by huang-kun on 04/02/2016.
//  Copyright (c) 2016 huang-kun. All rights reserved.
//

#import "YJViewController.h"
#import "UIImageView+YJCategory.h"

@interface YJViewController ()
@property (nonatomic, strong) IBOutlet UIImageView *imageView;
@end

@implementation YJViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.imageView.yj_contentMode = YJViewContentModeScaleAspectFit | YJViewContentModeTop;
}

@end
