//
//  ViewController.m
//  MetricaMobileDemo
//
//  Created by Irving  Medina on 06/08/12.
//  Copyright (c) 2012 logicoim@gmail.com. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize txtOne,txtTwo,txtError,txtResultado;
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

- (IBAction) triggerCrash {
	/* Trigger a crash */
    int value=[self.txtError.text intValue];
    switch (value)
    {
        case 1:
            CFRelease(NULL);
            break;
        case 2:
            [NSException raise:@"Test Crashes" format:@"It works!"];
            break;
        case 3:
            [self throwRandomException];
            break;
        
        default:
           CFRelease(NULL);
            break;
    }
	
}
-(void) throwExceptionInThread {
    dispatch_async( dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        sleep(3);
    });
    dispatch_async( dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // This thread should explode
        [NSException raise:@"Threaded Exception!" format:@"Exception error 4 type"];
    });
}

-(void) throwRandomException {
    NSString *alphabet  = @"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXZY0123456789";
    NSMutableString *s = [NSMutableString stringWithCapacity:20];
    for (NSUInteger i = 0U; i < 20; i++) {
        u_int32_t r = arc4random() % [alphabet length];
        unichar c = [alphabet characterAtIndex:r];
        [s appendFormat:@"%C", c];
    }
    [NSException raise:s format:@"Oops! an exception"];
}

- (IBAction) triggerExceptionCrash {
	/* Trigger a crash */
    NSArray *array = [NSArray array];
    [array objectAtIndex:23];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    //NSLog(@"touchesBegan:withEvent:");
    [self.view endEditing:YES];
    [super touchesBegan:touches withEvent:event];
}

-(IBAction)calcDivision:(id)sender{
    float resultado=0.0;
    int a=1, b=1;
    a=[self.txtOne.text intValue];
    b=[self.txtTwo.text intValue];
    resultado=a/b;
    
    //NSLog(@"%b / %b  = %f",a,b,resultado);
    NSString *msg= [[NSString alloc] initWithFormat:@"%10.2f",resultado];
    UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"Resultado" message:msg delegate:self cancelButtonTitle:@"Aceptar" otherButtonTitles:nil];
    [alert show];
    self.txtResultado.text= [NSString stringWithFormat:@"%10.2f", resultado];
    [txtOne resignFirstResponder];
    [txtTwo resignFirstResponder];
    //NSLog(@"El resultado es %f",resultado);
    
}

@end
