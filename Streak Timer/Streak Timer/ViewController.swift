//
//  ViewController.swift
//  Streak Timer
//
//  Created by Bill Addo on 4/3/17.
//  Copyright © 2017 Bill Addo. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    var swiftTimer = Timer()
    var swiftCounter = 0
    @IBAction func clearButton(sender: AnyObject) {
        swiftTimer.invalidate()
        swiftCounter = 0
        countingLabel.text = String(swiftCounter)
    }
    @IBOutlet var countingLabel: UILabel!
    
    @IBAction func startButton(sender: AnyObject) {
        swiftTimer = Timer.scheduledTimer(timeInterval: 1, target:self, selector: #selector(ViewController.updateCounter), userInfo: nil, repeats: true)

    }
    @IBAction func pauseButton(sender: AnyObject) {
    swiftTimer.invalidate()
    }
   
    
   
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        countingLabel.text = String(swiftCounter)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func updateCounter() {
        swiftCounter+=1
        countingLabel.text = String(swiftCounter)
    }


}

