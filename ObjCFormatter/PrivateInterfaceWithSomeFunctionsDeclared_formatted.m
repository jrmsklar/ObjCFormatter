//
//  BSLoginViewController.m
//  Some Project
//
//  Created by Josh Sklar on 8/21/13.
//  Copyright (c) 2013 Josh Sklar. All rights reserved.
//

#import "BSLoginViewController.h"

@interface BSLoginViewController () <UITextFieldDelegate>

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;
- (void)viewDidLoad;

/* Internal methods */
- (void)setupSignInView;
- (BOOL)validateFields;

/* UITextField delegate methods */
- (BOOL)textFieldShouldReturn:(UITextField *)textField;

- (void)setupView;
- (void)textFieldDidBeginEditing:(UITextField *)textField;

@end

@implementation BSLoginViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // code
}

#pragma mark - Internal methods

- (void)setupView
{
    // code
}

- (void)setupSignInView
{
    // code
}

- (BOOL)validateFields
{
    // code
    return YES;
}

#pragma mark - UITextField delegate methods

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    // code
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    // code
    return YES;
}

