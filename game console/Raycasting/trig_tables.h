/*
 * trig_tables.h
 *
 * Created: 26/09/2014 10:23:51 PM
 *  Author: Samuel
 */ 
// See trig_tables.c for generating options

#ifndef TRIG_TABLES_H_
#define TRIG_TABLES_H_

#include <avr/pgmspace.h>

#define NUM_TRIG_ELEMENTS 720

PROGMEM const float fsin[NUM_TRIG_ELEMENTS] = {
	0.0000,  0.0087,  0.0175,  0.0262,  0.0349,  0.0436,  0.0523,  0.0610,
	0.0698,  0.0785,  0.0872,  0.0958,  0.1045,  0.1132,  0.1219,  0.1305,
	0.1392,  0.1478,  0.1564,  0.1650,  0.1736,  0.1822,  0.1908,  0.1994,
	0.2079,  0.2164,  0.2250,  0.2334,  0.2419,  0.2504,  0.2588,  0.2672,
	0.2756,  0.2840,  0.2924,  0.3007,  0.3090,  0.3173,  0.3256,  0.3338,
	0.3420,  0.3502,  0.3584,  0.3665,  0.3746,  0.3827,  0.3907,  0.3987,
	0.4067,  0.4147,  0.4226,  0.4305,  0.4384,  0.4462,  0.4540,  0.4617,
	0.4695,  0.4772,  0.4848,  0.4924,  0.5000,  0.5075,  0.5150,  0.5225,
	0.5299,  0.5373,  0.5446,  0.5519,  0.5592,  0.5664,  0.5736,  0.5807,
	0.5878,  0.5948,  0.6018,  0.6088,  0.6157,  0.6225,  0.6293,  0.6361,
	0.6428,  0.6494,  0.6561,  0.6626,  0.6691,  0.6756,  0.6820,  0.6884,
	0.6947,  0.7009,  0.7071,  0.7133,  0.7193,  0.7254,  0.7314,  0.7373,
	0.7431,  0.7490,  0.7547,  0.7604,  0.7660,  0.7716,  0.7771,  0.7826,
	0.7880,  0.7934,  0.7986,  0.8039,  0.8090,  0.8141,  0.8192,  0.8241,
	0.8290,  0.8339,  0.8387,  0.8434,  0.8480,  0.8526,  0.8572,  0.8616,
	0.8660,  0.8704,  0.8746,  0.8788,  0.8829,  0.8870,  0.8910,  0.8949,
	0.8988,  0.9026,  0.9063,  0.9100,  0.9135,  0.9171,  0.9205,  0.9239,
	0.9272,  0.9304,  0.9336,  0.9367,  0.9397,  0.9426,  0.9455,  0.9483,
	0.9511,  0.9537,  0.9563,  0.9588,  0.9613,  0.9636,  0.9659,  0.9681,
	0.9703,  0.9724,  0.9744,  0.9763,  0.9781,  0.9799,  0.9816,  0.9833,
	0.9848,  0.9863,  0.9877,  0.9890,  0.9903,  0.9914,  0.9925,  0.9936,
	0.9945,  0.9954,  0.9962,  0.9969,  0.9976,  0.9981,  0.9986,  0.9990,
	0.9994,  0.9997,  0.9998,  1.0000,  1.0000,  1.0000,  0.9998,  0.9997,
	0.9994,  0.9990,  0.9986,  0.9981,  0.9976,  0.9969,  0.9962,  0.9954,
	0.9945,  0.9936,  0.9925,  0.9914,  0.9903,  0.9890,  0.9877,  0.9863,
	0.9848,  0.9833,  0.9816,  0.9799,  0.9781,  0.9763,  0.9744,  0.9724,
	0.9703,  0.9681,  0.9659,  0.9636,  0.9613,  0.9588,  0.9563,  0.9537,
	0.9511,  0.9483,  0.9455,  0.9426,  0.9397,  0.9367,  0.9336,  0.9304,
	0.9272,  0.9239,  0.9205,  0.9171,  0.9135,  0.9100,  0.9063,  0.9026,
	0.8988,  0.8949,  0.8910,  0.8870,  0.8829,  0.8788,  0.8746,  0.8704,
	0.8660,  0.8616,  0.8572,  0.8526,  0.8480,  0.8434,  0.8387,  0.8339,
	0.8290,  0.8241,  0.8192,  0.8141,  0.8090,  0.8039,  0.7986,  0.7934,
	0.7880,  0.7826,  0.7771,  0.7716,  0.7660,  0.7604,  0.7547,  0.7490,
	0.7431,  0.7373,  0.7314,  0.7254,  0.7193,  0.7133,  0.7071,  0.7009,
	0.6947,  0.6884,  0.6820,  0.6756,  0.6691,  0.6626,  0.6561,  0.6494,
	0.6428,  0.6361,  0.6293,  0.6225,  0.6157,  0.6088,  0.6018,  0.5948,
	0.5878,  0.5807,  0.5736,  0.5664,  0.5592,  0.5519,  0.5446,  0.5373,
	0.5299,  0.5225,  0.5150,  0.5075,  0.5000,  0.4924,  0.4848,  0.4772,
	0.4695,  0.4617,  0.4540,  0.4462,  0.4384,  0.4305,  0.4226,  0.4147,
	0.4067,  0.3987,  0.3907,  0.3827,  0.3746,  0.3665,  0.3584,  0.3502,
	0.3420,  0.3338,  0.3256,  0.3173,  0.3090,  0.3007,  0.2924,  0.2840,
	0.2756,  0.2672,  0.2588,  0.2504,  0.2419,  0.2334,  0.2250,  0.2164,
	0.2079,  0.1994,  0.1908,  0.1822,  0.1736,  0.1650,  0.1564,  0.1478,
	0.1392,  0.1305,  0.1219,  0.1132,  0.1045,  0.0958,  0.0872,  0.0785,
	0.0698,  0.0610,  0.0523,  0.0436,  0.0349,  0.0262,  0.0175,  0.0087,
	0.0000, -0.0087, -0.0175, -0.0262, -0.0349, -0.0436, -0.0523, -0.0610,
	-0.0698, -0.0785, -0.0872, -0.0958, -0.1045, -0.1132, -0.1219, -0.1305,
	-0.1392, -0.1478, -0.1564, -0.1650, -0.1736, -0.1822, -0.1908, -0.1994,
	-0.2079, -0.2164, -0.2250, -0.2334, -0.2419, -0.2504, -0.2588, -0.2672,
	-0.2756, -0.2840, -0.2924, -0.3007, -0.3090, -0.3173, -0.3256, -0.3338,
	-0.3420, -0.3502, -0.3584, -0.3665, -0.3746, -0.3827, -0.3907, -0.3987,
	-0.4067, -0.4147, -0.4226, -0.4305, -0.4384, -0.4462, -0.4540, -0.4617,
	-0.4695, -0.4772, -0.4848, -0.4924, -0.5000, -0.5075, -0.5150, -0.5225,
	-0.5299, -0.5373, -0.5446, -0.5519, -0.5592, -0.5664, -0.5736, -0.5807,
	-0.5878, -0.5948, -0.6018, -0.6088, -0.6157, -0.6225, -0.6293, -0.6361,
	-0.6428, -0.6494, -0.6561, -0.6626, -0.6691, -0.6756, -0.6820, -0.6884,
	-0.6947, -0.7009, -0.7071, -0.7133, -0.7193, -0.7254, -0.7314, -0.7373,
	-0.7431, -0.7490, -0.7547, -0.7604, -0.7660, -0.7716, -0.7771, -0.7826,
	-0.7880, -0.7934, -0.7986, -0.8039, -0.8090, -0.8141, -0.8192, -0.8241,
	-0.8290, -0.8339, -0.8387, -0.8434, -0.8480, -0.8526, -0.8572, -0.8616,
	-0.8660, -0.8704, -0.8746, -0.8788, -0.8829, -0.8870, -0.8910, -0.8949,
	-0.8988, -0.9026, -0.9063, -0.9100, -0.9135, -0.9171, -0.9205, -0.9239,
	-0.9272, -0.9304, -0.9336, -0.9367, -0.9397, -0.9426, -0.9455, -0.9483,
	-0.9511, -0.9537, -0.9563, -0.9588, -0.9613, -0.9636, -0.9659, -0.9681,
	-0.9703, -0.9724, -0.9744, -0.9763, -0.9781, -0.9799, -0.9816, -0.9833,
	-0.9848, -0.9863, -0.9877, -0.9890, -0.9903, -0.9914, -0.9925, -0.9936,
	-0.9945, -0.9954, -0.9962, -0.9969, -0.9976, -0.9981, -0.9986, -0.9990,
	-0.9994, -0.9997, -0.9998, -1.0000, -1.0000, -1.0000, -0.9998, -0.9997,
	-0.9994, -0.9990, -0.9986, -0.9981, -0.9976, -0.9969, -0.9962, -0.9954,
	-0.9945, -0.9936, -0.9925, -0.9914, -0.9903, -0.9890, -0.9877, -0.9863,
	-0.9848, -0.9833, -0.9816, -0.9799, -0.9781, -0.9763, -0.9744, -0.9724,
	-0.9703, -0.9681, -0.9659, -0.9636, -0.9613, -0.9588, -0.9563, -0.9537,
	-0.9511, -0.9483, -0.9455, -0.9426, -0.9397, -0.9367, -0.9336, -0.9304,
	-0.9272, -0.9239, -0.9205, -0.9171, -0.9135, -0.9100, -0.9063, -0.9026,
	-0.8988, -0.8949, -0.8910, -0.8870, -0.8829, -0.8788, -0.8746, -0.8704,
	-0.8660, -0.8616, -0.8572, -0.8526, -0.8480, -0.8434, -0.8387, -0.8339,
	-0.8290, -0.8241, -0.8192, -0.8141, -0.8090, -0.8039, -0.7986, -0.7934,
	-0.7880, -0.7826, -0.7771, -0.7716, -0.7660, -0.7604, -0.7547, -0.7490,
	-0.7431, -0.7373, -0.7314, -0.7254, -0.7193, -0.7133, -0.7071, -0.7009,
	-0.6947, -0.6884, -0.6820, -0.6756, -0.6691, -0.6626, -0.6561, -0.6494,
	-0.6428, -0.6361, -0.6293, -0.6225, -0.6157, -0.6088, -0.6018, -0.5948,
	-0.5878, -0.5807, -0.5736, -0.5664, -0.5592, -0.5519, -0.5446, -0.5373,
	-0.5299, -0.5225, -0.5150, -0.5075, -0.5000, -0.4924, -0.4848, -0.4772,
	-0.4695, -0.4617, -0.4540, -0.4462, -0.4384, -0.4305, -0.4226, -0.4147,
	-0.4067, -0.3987, -0.3907, -0.3827, -0.3746, -0.3665, -0.3584, -0.3502,
	-0.3420, -0.3338, -0.3256, -0.3173, -0.3090, -0.3007, -0.2924, -0.2840,
	-0.2756, -0.2672, -0.2588, -0.2504, -0.2419, -0.2334, -0.2250, -0.2164,
	-0.2079, -0.1994, -0.1908, -0.1822, -0.1736, -0.1650, -0.1564, -0.1478,
	-0.1392, -0.1305, -0.1219, -0.1132, -0.1045, -0.0958, -0.0872, -0.0785,
	-0.0698, -0.0610, -0.0523, -0.0436, -0.0349, -0.0262, -0.0175, -0.0087,
};

PROGMEM const float fcos[NUM_TRIG_ELEMENTS] = {
	1.0000,  1.0000,  0.9998,  0.9997,  0.9994,  0.9990,  0.9986,  0.9981,
	0.9976,  0.9969,  0.9962,  0.9954,  0.9945,  0.9936,  0.9925,  0.9914,
	0.9903,  0.9890,  0.9877,  0.9863,  0.9848,  0.9833,  0.9816,  0.9799,
	0.9781,  0.9763,  0.9744,  0.9724,  0.9703,  0.9681,  0.9659,  0.9636,
	0.9613,  0.9588,  0.9563,  0.9537,  0.9511,  0.9483,  0.9455,  0.9426,
	0.9397,  0.9367,  0.9336,  0.9304,  0.9272,  0.9239,  0.9205,  0.9171,
	0.9135,  0.9100,  0.9063,  0.9026,  0.8988,  0.8949,  0.8910,  0.8870,
	0.8829,  0.8788,  0.8746,  0.8704,  0.8660,  0.8616,  0.8572,  0.8526,
	0.8480,  0.8434,  0.8387,  0.8339,  0.8290,  0.8241,  0.8192,  0.8141,
	0.8090,  0.8039,  0.7986,  0.7934,  0.7880,  0.7826,  0.7771,  0.7716,
	0.7660,  0.7604,  0.7547,  0.7490,  0.7431,  0.7373,  0.7314,  0.7254,
	0.7193,  0.7133,  0.7071,  0.7009,  0.6947,  0.6884,  0.6820,  0.6756,
	0.6691,  0.6626,  0.6561,  0.6494,  0.6428,  0.6361,  0.6293,  0.6225,
	0.6157,  0.6088,  0.6018,  0.5948,  0.5878,  0.5807,  0.5736,  0.5664,
	0.5592,  0.5519,  0.5446,  0.5373,  0.5299,  0.5225,  0.5150,  0.5075,
	0.5000,  0.4924,  0.4848,  0.4772,  0.4695,  0.4617,  0.4540,  0.4462,
	0.4384,  0.4305,  0.4226,  0.4147,  0.4067,  0.3987,  0.3907,  0.3827,
	0.3746,  0.3665,  0.3584,  0.3502,  0.3420,  0.3338,  0.3256,  0.3173,
	0.3090,  0.3007,  0.2924,  0.2840,  0.2756,  0.2672,  0.2588,  0.2504,
	0.2419,  0.2334,  0.2250,  0.2164,  0.2079,  0.1994,  0.1908,  0.1822,
	0.1736,  0.1650,  0.1564,  0.1478,  0.1392,  0.1305,  0.1219,  0.1132,
	0.1045,  0.0958,  0.0872,  0.0785,  0.0698,  0.0610,  0.0523,  0.0436,
	0.0349,  0.0262,  0.0175,  0.0087,  0.0000, -0.0087, -0.0175, -0.0262,
	-0.0349, -0.0436, -0.0523, -0.0610, -0.0698, -0.0785, -0.0872, -0.0958,
	-0.1045, -0.1132, -0.1219, -0.1305, -0.1392, -0.1478, -0.1564, -0.1650,
	-0.1736, -0.1822, -0.1908, -0.1994, -0.2079, -0.2164, -0.2250, -0.2334,
	-0.2419, -0.2504, -0.2588, -0.2672, -0.2756, -0.2840, -0.2924, -0.3007,
	-0.3090, -0.3173, -0.3256, -0.3338, -0.3420, -0.3502, -0.3584, -0.3665,
	-0.3746, -0.3827, -0.3907, -0.3987, -0.4067, -0.4147, -0.4226, -0.4305,
	-0.4384, -0.4462, -0.4540, -0.4617, -0.4695, -0.4772, -0.4848, -0.4924,
	-0.5000, -0.5075, -0.5150, -0.5225, -0.5299, -0.5373, -0.5446, -0.5519,
	-0.5592, -0.5664, -0.5736, -0.5807, -0.5878, -0.5948, -0.6018, -0.6088,
	-0.6157, -0.6225, -0.6293, -0.6361, -0.6428, -0.6494, -0.6561, -0.6626,
	-0.6691, -0.6756, -0.6820, -0.6884, -0.6947, -0.7009, -0.7071, -0.7133,
	-0.7193, -0.7254, -0.7314, -0.7373, -0.7431, -0.7490, -0.7547, -0.7604,
	-0.7660, -0.7716, -0.7771, -0.7826, -0.7880, -0.7934, -0.7986, -0.8039,
	-0.8090, -0.8141, -0.8192, -0.8241, -0.8290, -0.8339, -0.8387, -0.8434,
	-0.8480, -0.8526, -0.8572, -0.8616, -0.8660, -0.8704, -0.8746, -0.8788,
	-0.8829, -0.8870, -0.8910, -0.8949, -0.8988, -0.9026, -0.9063, -0.9100,
	-0.9135, -0.9171, -0.9205, -0.9239, -0.9272, -0.9304, -0.9336, -0.9367,
	-0.9397, -0.9426, -0.9455, -0.9483, -0.9511, -0.9537, -0.9563, -0.9588,
	-0.9613, -0.9636, -0.9659, -0.9681, -0.9703, -0.9724, -0.9744, -0.9763,
	-0.9781, -0.9799, -0.9816, -0.9833, -0.9848, -0.9863, -0.9877, -0.9890,
	-0.9903, -0.9914, -0.9925, -0.9936, -0.9945, -0.9954, -0.9962, -0.9969,
	-0.9976, -0.9981, -0.9986, -0.9990, -0.9994, -0.9997, -0.9998, -1.0000,
	-1.0000, -1.0000, -0.9998, -0.9997, -0.9994, -0.9990, -0.9986, -0.9981,
	-0.9976, -0.9969, -0.9962, -0.9954, -0.9945, -0.9936, -0.9925, -0.9914,
	-0.9903, -0.9890, -0.9877, -0.9863, -0.9848, -0.9833, -0.9816, -0.9799,
	-0.9781, -0.9763, -0.9744, -0.9724, -0.9703, -0.9681, -0.9659, -0.9636,
	-0.9613, -0.9588, -0.9563, -0.9537, -0.9511, -0.9483, -0.9455, -0.9426,
	-0.9397, -0.9367, -0.9336, -0.9304, -0.9272, -0.9239, -0.9205, -0.9171,
	-0.9135, -0.9100, -0.9063, -0.9026, -0.8988, -0.8949, -0.8910, -0.8870,
	-0.8829, -0.8788, -0.8746, -0.8704, -0.8660, -0.8616, -0.8572, -0.8526,
	-0.8480, -0.8434, -0.8387, -0.8339, -0.8290, -0.8241, -0.8192, -0.8141,
	-0.8090, -0.8039, -0.7986, -0.7934, -0.7880, -0.7826, -0.7771, -0.7716,
	-0.7660, -0.7604, -0.7547, -0.7490, -0.7431, -0.7373, -0.7314, -0.7254,
	-0.7193, -0.7133, -0.7071, -0.7009, -0.6947, -0.6884, -0.6820, -0.6756,
	-0.6691, -0.6626, -0.6561, -0.6494, -0.6428, -0.6361, -0.6293, -0.6225,
	-0.6157, -0.6088, -0.6018, -0.5948, -0.5878, -0.5807, -0.5736, -0.5664,
	-0.5592, -0.5519, -0.5446, -0.5373, -0.5299, -0.5225, -0.5150, -0.5075,
	-0.5000, -0.4924, -0.4848, -0.4772, -0.4695, -0.4617, -0.4540, -0.4462,
	-0.4384, -0.4305, -0.4226, -0.4147, -0.4067, -0.3987, -0.3907, -0.3827,
	-0.3746, -0.3665, -0.3584, -0.3502, -0.3420, -0.3338, -0.3256, -0.3173,
	-0.3090, -0.3007, -0.2924, -0.2840, -0.2756, -0.2672, -0.2588, -0.2504,
	-0.2419, -0.2334, -0.2250, -0.2164, -0.2079, -0.1994, -0.1908, -0.1822,
	-0.1736, -0.1650, -0.1564, -0.1478, -0.1392, -0.1305, -0.1219, -0.1132,
	-0.1045, -0.0958, -0.0872, -0.0785, -0.0698, -0.0610, -0.0523, -0.0436,
	-0.0349, -0.0262, -0.0175, -0.0087, -0.0000,  0.0087,  0.0175,  0.0262,
	0.0349,  0.0436,  0.0523,  0.0610,  0.0698,  0.0785,  0.0872,  0.0958,
	0.1045,  0.1132,  0.1219,  0.1305,  0.1392,  0.1478,  0.1564,  0.1650,
	0.1736,  0.1822,  0.1908,  0.1994,  0.2079,  0.2164,  0.2250,  0.2334,
	0.2419,  0.2504,  0.2588,  0.2672,  0.2756,  0.2840,  0.2924,  0.3007,
	0.3090,  0.3173,  0.3256,  0.3338,  0.3420,  0.3502,  0.3584,  0.3665,
	0.3746,  0.3827,  0.3907,  0.3987,  0.4067,  0.4147,  0.4226,  0.4305,
	0.4384,  0.4462,  0.4540,  0.4617,  0.4695,  0.4772,  0.4848,  0.4924,
	0.5000,  0.5075,  0.5150,  0.5225,  0.5299,  0.5373,  0.5446,  0.5519,
	0.5592,  0.5664,  0.5736,  0.5807,  0.5878,  0.5948,  0.6018,  0.6088,
	0.6157,  0.6225,  0.6293,  0.6361,  0.6428,  0.6494,  0.6561,  0.6626,
	0.6691,  0.6756,  0.6820,  0.6884,  0.6947,  0.7009,  0.7071,  0.7133,
	0.7193,  0.7254,  0.7314,  0.7373,  0.7431,  0.7490,  0.7547,  0.7604,
	0.7660,  0.7716,  0.7771,  0.7826,  0.7880,  0.7934,  0.7986,  0.8039,
	0.8090,  0.8141,  0.8192,  0.8241,  0.8290,  0.8339,  0.8387,  0.8434,
	0.8480,  0.8526,  0.8572,  0.8616,  0.8660,  0.8704,  0.8746,  0.8788,
	0.8829,  0.8870,  0.8910,  0.8949,  0.8988,  0.9026,  0.9063,  0.9100,
	0.9135,  0.9171,  0.9205,  0.9239,  0.9272,  0.9304,  0.9336,  0.9367,
	0.9397,  0.9426,  0.9455,  0.9483,  0.9511,  0.9537,  0.9563,  0.9588,
	0.9613,  0.9636,  0.9659,  0.9681,  0.9703,  0.9724,  0.9744,  0.9763,
	0.9781,  0.9799,  0.9816,  0.9833,  0.9848,  0.9863,  0.9877,  0.9890,
	0.9903,  0.9914,  0.9925,  0.9936,  0.9945,  0.9954,  0.9962,  0.9969,
	0.9976,  0.9981,  0.9986,  0.9990,  0.9994,  0.9997,  0.9998,  1.0000,
};

PROGMEM const float ftan[NUM_TRIG_ELEMENTS] = {
	0.0000,   0.0087,   0.0175,   0.0262,   0.0349,   0.0437,   0.0524,   0.0612,
	0.0699,   0.0787,   0.0875,   0.0963,   0.1051,   0.1139,   0.1228,   0.1317,
	0.1405,   0.1495,   0.1584,   0.1673,   0.1763,   0.1853,   0.1944,   0.2035,
	0.2126,   0.2217,   0.2309,   0.2401,   0.2493,   0.2586,   0.2679,   0.2773,
	0.2867,   0.2962,   0.3057,   0.3153,   0.3249,   0.3346,   0.3443,   0.3541,
	0.3640,   0.3739,   0.3839,   0.3939,   0.4040,   0.4142,   0.4245,   0.4348,
	0.4452,   0.4557,   0.4663,   0.4770,   0.4877,   0.4986,   0.5095,   0.5206,
	0.5317,   0.5430,   0.5543,   0.5658,   0.5774,   0.5890,   0.6009,   0.6128,
	0.6249,   0.6371,   0.6494,   0.6619,   0.6745,   0.6873,   0.7002,   0.7133,
	0.7265,   0.7400,   0.7536,   0.7673,   0.7813,   0.7954,   0.8098,   0.8243,
	0.8391,   0.8541,   0.8693,   0.8847,   0.9004,   0.9163,   0.9325,   0.9490,
	0.9657,   0.9827,   1.0000,   1.0176,   1.0355,   1.0538,   1.0724,   1.0913,
	1.1106,   1.1303,   1.1504,   1.1708,   1.1918,   1.2131,   1.2349,   1.2572,
	1.2799,   1.3032,   1.3270,   1.3514,   1.3764,   1.4019,   1.4281,   1.4550,
	1.4826,   1.5108,   1.5399,   1.5697,   1.6003,   1.6319,   1.6643,   1.6977,
	1.7321,   1.7675,   1.8040,   1.8418,   1.8807,   1.9210,   1.9626,   2.0057,
	2.0503,   2.0965,   2.1445,   2.1943,   2.2460,   2.2998,   2.3559,   2.4142,
	2.4751,   2.5386,   2.6051,   2.6746,   2.7475,   2.8239,   2.9042,   2.9887,
	3.0777,   3.1716,   3.2709,   3.3759,   3.4874,   3.6059,   3.7321,   3.8667,
	4.0108,   4.1653,   4.3315,   4.5107,   4.7046,   4.9152,   5.1446,   5.3955,
	5.6713,   5.9758,   6.3138,   6.6912,   7.1154,   7.5958,   8.1443,   8.7769,
	9.5144,  10.3854,  11.4301,  12.7062,  14.3007,  16.3499,  19.0811,  22.9038,
	28.6363,  38.1885,  57.2900, 114.5887,  1000000, -114.5887, -57.2900, -38.1885
	-28.6363, -22.9038, -19.0811, -16.3499, -14.3007, -12.7062, -11.4301, -10.3854,
	-9.5144,  -8.7769,  -8.1443,  -7.5958,  -7.1154,  -6.6912,  -6.3138,  -5.9758,
	-5.6713,  -5.3955,  -5.1446,  -4.9152,  -4.7046,  -4.5107,  -4.3315,  -4.1653,
	-4.0108,  -3.8667,  -3.7321,  -3.6059,  -3.4874,  -3.3759,  -3.2709,  -3.1716,
	-3.0777,  -2.9887,  -2.9042,  -2.8239,  -2.7475,  -2.6746,  -2.6051,  -2.5386,
	-2.4751,  -2.4142,  -2.3559,  -2.2998,  -2.2460,  -2.1943,  -2.1445,  -2.0965,
	-2.0503,  -2.0057,  -1.9626,  -1.9210,  -1.8807,  -1.8418,  -1.8040,  -1.7675,
	-1.7321,  -1.6977,  -1.6643,  -1.6319,  -1.6003,  -1.5697,  -1.5399,  -1.5108,
	-1.4826,  -1.4550,  -1.4281,  -1.4019,  -1.3764,  -1.3514,  -1.3270,  -1.3032,
	-1.2799,  -1.2572,  -1.2349,  -1.2131,  -1.1918,  -1.1708,  -1.1504,  -1.1303,
	-1.1106,  -1.0913,  -1.0724,  -1.0538,  -1.0355,  -1.0176,  -1.0000,  -0.9827,
	-0.9657,  -0.9490,  -0.9325,  -0.9163,  -0.9004,  -0.8847,  -0.8693,  -0.8541,
	-0.8391,  -0.8243,  -0.8098,  -0.7954,  -0.7813,  -0.7673,  -0.7536,  -0.7400,
	-0.7265,  -0.7133,  -0.7002,  -0.6873,  -0.6745,  -0.6619,  -0.6494,  -0.6371,
	-0.6249,  -0.6128,  -0.6009,  -0.5890,  -0.5774,  -0.5658,  -0.5543,  -0.5430,
	-0.5317,  -0.5206,  -0.5095,  -0.4986,  -0.4877,  -0.4770,  -0.4663,  -0.4557,
	-0.4452,  -0.4348,  -0.4245,  -0.4142,  -0.4040,  -0.3939,  -0.3839,  -0.3739,
	-0.3640,  -0.3541,  -0.3443,  -0.3346,  -0.3249,  -0.3153,  -0.3057,  -0.2962,
	-0.2867,  -0.2773,  -0.2679,  -0.2586,  -0.2493,  -0.2401,  -0.2309,  -0.2217,
	-0.2126,  -0.2035,  -0.1944,  -0.1853,  -0.1763,  -0.1673,  -0.1584,  -0.1495,
	-0.1405,  -0.1317,  -0.1228,  -0.1139,  -0.1051,  -0.0963,  -0.0875,  -0.0787,
	-0.0699,  -0.0612,  -0.0524,  -0.0437,  -0.0349,  -0.0262,  -0.0175,  -0.0087,
	-0.0000,   0.0087,   0.0175,   0.0262,   0.0349,   0.0437,   0.0524,   0.0612,
	0.0699,   0.0787,   0.0875,   0.0963,   0.1051,   0.1139,   0.1228,   0.1317,
	0.1405,   0.1495,   0.1584,   0.1673,   0.1763,   0.1853,   0.1944,   0.2035,
	0.2126,   0.2217,   0.2309,   0.2401,   0.2493,   0.2586,   0.2679,   0.2773,
	0.2867,   0.2962,   0.3057,   0.3153,   0.3249,   0.3346,   0.3443,   0.3541,
	0.3640,   0.3739,   0.3839,   0.3939,   0.4040,   0.4142,   0.4245,   0.4348,
	0.4452,   0.4557,   0.4663,   0.4770,   0.4877,   0.4986,   0.5095,   0.5206,
	0.5317,   0.5430,   0.5543,   0.5658,   0.5774,   0.5890,   0.6009,   0.6128,
	0.6249,   0.6371,   0.6494,   0.6619,   0.6745,   0.6873,   0.7002,   0.7133,
	0.7265,   0.7400,   0.7536,   0.7673,   0.7813,   0.7954,   0.8098,   0.8243,
	0.8391,   0.8541,   0.8693,   0.8847,   0.9004,   0.9163,   0.9325,   0.9490,
	0.9657,   0.9827,   1.0000,   1.0176,   1.0355,   1.0538,   1.0724,   1.0913,
	1.1106,   1.1303,   1.1504,   1.1708,   1.1918,   1.2131,   1.2349,   1.2572,
	1.2799,   1.3032,   1.3270,   1.3514,   1.3764,   1.4019,   1.4281,   1.4550,
	1.4826,   1.5108,   1.5399,   1.5697,   1.6003,   1.6319,   1.6643,   1.6977,
	1.7321,   1.7675,   1.8040,   1.8418,   1.8807,   1.9210,   1.9626,   2.0057,
	2.0503,   2.0965,   2.1445,   2.1943,   2.2460,   2.2998,   2.3559,   2.4142,
	2.4751,   2.5386,   2.6051,   2.6746,   2.7475,   2.8239,   2.9042,   2.9887,
	3.0777,   3.1716,   3.2709,   3.3759,   3.4874,   3.6059,   3.7321,   3.8667,
	4.0108,   4.1653,   4.3315,   4.5107,   4.7046,   4.9152,   5.1446,   5.3955,
	5.6713,   5.9758,   6.3138,   6.6912,   7.1154,   7.5958,   8.1443,   8.7769,
	9.5144,  10.3854,  11.4301,  12.7062,  14.3007,  16.3499,  19.0811,  22.9038,
	28.6363,  38.1885,  57.2900, 114.5887,  1000000, -114.5887, -57.2900, -38.1885
	-28.6363, -22.9038, -19.0811, -16.3499, -14.3007, -12.7062, -11.4301, -10.3854,
	-9.5144,  -8.7769,  -8.1443,  -7.5958,  -7.1154,  -6.6912,  -6.3138,  -5.9758,
	-5.6713,  -5.3955,  -5.1446,  -4.9152,  -4.7046,  -4.5107,  -4.3315,  -4.1653,
	-4.0108,  -3.8667,  -3.7321,  -3.6059,  -3.4874,  -3.3759,  -3.2709,  -3.1716,
	-3.0777,  -2.9887,  -2.9042,  -2.8239,  -2.7475,  -2.6746,  -2.6051,  -2.5386,
	-2.4751,  -2.4142,  -2.3559,  -2.2998,  -2.2460,  -2.1943,  -2.1445,  -2.0965,
	-2.0503,  -2.0057,  -1.9626,  -1.9210,  -1.8807,  -1.8418,  -1.8040,  -1.7675,
	-1.7321,  -1.6977,  -1.6643,  -1.6319,  -1.6003,  -1.5697,  -1.5399,  -1.5108,
	-1.4826,  -1.4550,  -1.4281,  -1.4019,  -1.3764,  -1.3514,  -1.3270,  -1.3032,
	-1.2799,  -1.2572,  -1.2349,  -1.2131,  -1.1918,  -1.1708,  -1.1504,  -1.1303,
	-1.1106,  -1.0913,  -1.0724,  -1.0538,  -1.0355,  -1.0176,  -1.0000,  -0.9827,
	-0.9657,  -0.9490,  -0.9325,  -0.9163,  -0.9004,  -0.8847,  -0.8693,  -0.8541,
	-0.8391,  -0.8243,  -0.8098,  -0.7954,  -0.7813,  -0.7673,  -0.7536,  -0.7400,
	-0.7265,  -0.7133,  -0.7002,  -0.6873,  -0.6745,  -0.6619,  -0.6494,  -0.6371,
	-0.6249,  -0.6128,  -0.6009,  -0.5890,  -0.5774,  -0.5658,  -0.5543,  -0.5430,
	-0.5317,  -0.5206,  -0.5095,  -0.4986,  -0.4877,  -0.4770,  -0.4663,  -0.4557,
	-0.4452,  -0.4348,  -0.4245,  -0.4142,  -0.4040,  -0.3939,  -0.3839,  -0.3739,
	-0.3640,  -0.3541,  -0.3443,  -0.3346,  -0.3249,  -0.3153,  -0.3057,  -0.2962,
	-0.2867,  -0.2773,  -0.2679,  -0.2586,  -0.2493,  -0.2401,  -0.2309,  -0.2217,
	-0.2126,  -0.2035,  -0.1944,  -0.1853,  -0.1763,  -0.1673,  -0.1584,  -0.1495,
	-0.1405,  -0.1317,  -0.1228,  -0.1139,  -0.1051,  -0.0963,  -0.0875,  -0.0787,
	-0.0699,  -0.0612,  -0.0524,  -0.0437,  -0.0349,  -0.0262,  -0.0175,  -0.0087
};
#endif /* TRIG_TABLES_H_ */