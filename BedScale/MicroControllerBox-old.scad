clearance = 0.5;
shell = 1.5;

module ESP() {
	translate([-59/2,0,6])
	cube([6.2,8.2,3.2], center=true);
	cube([59,31,11.5], center=true);
	
}

module HX711() {
	cube([21,35, 11.5], center=true); // HX711
}

module 9V() {
	cube([48,25,15], center=true);
}

module Electronics() {
	translate([-30,0,0]) ESP();
	translate([11,2,0]) HX711();
	translate([-24.5, 16+13+1,0]) 9V();
}

module ElectronicsShell() {
	
	difference() {

		cube([59+21+3+3+shell+shell, 31+3+25+3+shell+shell,15+3], center=true); //outer case
		translate([0,0,shell])
		cube([59+21+3+3, 31+3+25+3,15+3], center=true); // inner shell
	
	translate([17,-13, 0]) Electronics();
	
	translate([-25,0,5])
	cube([10, 200,4], center=true);
	
	mirror([1,0,0])
	translate([-25,0,5])
	cube([10, 200,4], center=true);
	}
	
	translate([0,(31+25+3+3)/2-0.25,(15+3)/2-0.5])
	Notch(20);
	
	mirror([0,1,0])
	translate([0,(31+25+3+3)/2-0.25,(15+3)/2-0.5])
	Notch(20);
	
	
	translate([(59+21+3+3)/2,0,(15+3)/2-0.5])
	rotate([00,0,-90])
	Notch(10);
	
	mirror([1,0,0])
	translate([(59+21+3+3)/2,0,(15+3)/2-0.5])
	rotate([00,0,-90])
	Notch(10);
}

	ElectronicsShell();

	%translate([17,-13, 0])
	Electronics();



module Notch(h=5) {
	rotate([30,0,0])
	rotate([0,90,0])
	cylinder(r=0.5, h = h, $fn=3, center=true);
}

*Notch();