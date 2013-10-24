## Objective-C Formatter

***C++ based Objective-C formatter. Cleans up Objective-C code, making it easier to work on.***

Overview
------------

Objective-C Formatter is a C++ program used to format Objective-C files.

Formatting Options:

1. Put all function declarations in a `.m` file into the private `@interface` of a .m file.
2. More to come in the future.


Instructions
------------
The program resides in `format.cpp`. Begin by compiling `format.cpp`. Do this by using the Makefile, or typing `make` onto the command line.

The Makefile generates an executable titled `format`. `format` takes either 1 or 2 extra arguments on the command line. The first argument that it takes is required, and is the full path of the input file to be formatted. This must be a `.m` file. The second argument is optional, and is the full path for the ouput file. If this argument is not specified, `format` will overwrite the input file. If this argument is specified, it will write to this file.

***Notes***

1. in `format.cpp`'s current state, the `.m` it must have a private `@interface`.
2. In its current state, the `.m` file must have all of the brackets following the function declaration on a new line. Ie:

```objective-c
- (void)someFunction
{
}

// NOT
- (void)someFunction{
}
```

Example
-------
`BSLoginViewController.m` (see below) was formatted using `format`, using the following commands:

```
make
./format BSLoginViewController.m
```

***Before***

```objective-c
//
//  BSLoginViewController.m
//  Some Project
//
//  Created by Josh Sklar on 8/21/13.
//  Copyright (c) 2013 Josh Sklar. All rights reserved.
//

#import "BSLoginViewController.h"

@interface BSLoginViewController () <UITextFieldDelegate>

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

@end
```

***After***

```objective-c
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
- (void)setupView;
- (void)setupSignInView;
- (BOOL)validateFields;

/* UITextField delegate methods */
- (void)textFieldDidBeginEditing:(UITextField *)textField;
- (BOOL)textFieldShouldReturn:(UITextField *)textField;

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


```



Future
-------

In the future, I plan on creating an ouput file showing the diff of the input file and the result.

I also plan on creating a lot more formatting options.

