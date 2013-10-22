//
//  FFGamesListBackgroundView.m
//  Amicus
//
//  Created by Josh Sklar on 4/15/13.
//  Copyright (c) 2013 Josh Sklar. All rights reserved.
//

#import "FFGamesListBackgroundView.h"
#import "FFGamesListViewController.h"
#import "JSButton.h"
#import "UIView+Positioning.h"


static const CGFloat kBtnWidth = 160.;
static const CGFloat kBtnHeight = 115.;

@interface FFGamesListBackgroundView ()

- (id)initWithFrame:(CGRect)frame andGamesList:(FFGamesListViewController*)gamesList;
- (void)notImplementedYet;

@end

@implementation FFGamesListBackgroundView

- (id)initWithFrame:(CGRect)frame andGamesList:(FFGamesListViewController*)gamesList
{
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        UIButton *recordButton = [[UIButton alloc]initWithFrame:CGRectMake(0, 20, kBtnWidth, kBtnHeight)];
        [recordButton addTarget:gamesList action:@selector(didTapShowRecords) forControlEvents:UIControlEventTouchUpInside];
        [recordButton setBackgroundImage:[UIImage imageNamed:@"records-button"] forState:UIControlStateNormal];
        [self addSubview:recordButton];
        
        UIButton *myAccountButton = [[UIButton alloc]initWithFrame:CGRectMake([recordButton getLocationOfRight], 20, kBtnWidth, kBtnHeight)];
        [myAccountButton addTarget:gamesList action:@selector(didTapShowMyAccount) forControlEvents:UIControlEventTouchUpInside];
        [myAccountButton setBackgroundImage:[UIImage imageNamed:@"my-account-button"] forState:UIControlStateNormal];
        [self addSubview:myAccountButton];
        
        /*
         
         UIButton *deleteAllButton = [[UIButton alloc]initWithFrame:CGRectMake(0, [recordButton getLocationOfBottom], kBtnWidth, kBtnHeight)];
         [deleteAllButton addTarget:self action:@selector(notImplementedYet) forControlEvents:UIControlEventTouchUpInside];
         [deleteAllButton setBackgroundImage:[UIImage imageNamed:@"trash-button"] forState:UIControlStateNormal];
         [self addSubview:deleteAllButton];
         
         
         UIButton *soundFXButton = [[UIButton alloc]initWithFrame:CGRectMake([deleteAllButton getLocationOfRight], [myAccountButton getLocationOfBottom], kBtnWidth, kBtnHeight)];
         [soundFXButton addTarget:self action:@selector(notImplementedYet) forControlEvents:UIControlEventTouchUpInside];
         [soundFXButton setBackgroundImage:[UIImage imageNamed:@"sound-fx-button"] forState:UIControlStateNormal];
         [self addSubview:soundFXButton];
         */
    }
    return self;
}

- (void)notImplementedYet
{
    [[[UIAlertView alloc]initWithTitle:@"Feature not available in this version." message:nil delegate:nil cancelButtonTitle:@"Dismiss" otherButtonTitles:nil]show];
}

@end
