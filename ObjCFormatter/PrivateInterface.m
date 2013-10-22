//
//  MGDetailTableViewController.m
//  Merge-Admin
//
//  Created by Josh Sklar on 9/28/13.
//  Copyright (c) 2013 Merge. All rights reserved.
//

#import "MGDetailTableViewController.h"
#import <Parse/Parse.h>

@interface MGDetailTableViewController ()

@end

@implementation MGDetailTableViewController


#pragma mark - UITableview data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.data.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *cellID = @"cellID";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellID];
    }
    
    if (!self.formatBlock) {
        [cell.textLabel setText:@"Something went wrong. No formatBlock property in MGDetailTableViewController"];
        return cell;
    }
    
    PFObject *obj = [self.data objectAtIndex:indexPath.row];
    
    NSDictionary *cellText = self.formatBlock(obj);
    
    [cell.textLabel setText:cellText[@"textLabelText"]];
    [cell.detailTextLabel setText:cellText[@"detailLabelText"]];
    
    return cell;
}

#pragma mark - UITableViewDelegate methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

@end
