//
//  ViewController.h
//  MetricaMobileDemo
//
//  Created by Irving  Medina on 06/08/12.
//  Copyright (c) 2012 logicoim@gmail.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController{
    UILabel *txtResultado;
    UITextField *txtOne,*txtTwo,*txtError;
}
@property (nonatomic,strong) IBOutlet UILabel *txtResultado;
@property (nonatomic,strong) IBOutlet UITextField *txtOne,*txtTwo,*txtError;

-(IBAction)calcDivision:(id)sender;
-(void) throwExceptionInThread;
-(void) throwRandomException; 
- (IBAction) triggerCrash;
- (IBAction) triggerExceptionCrash;

@end
