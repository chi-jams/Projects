extern crate clap;
extern crate synthrs;

use clap::{Arg, App};
use std::env;
use synthrs::synthesizer::{ make_samples, quantize_samples };
use synthrs::wave::sine_wave;
use synthrs::writer::write_wav_file;

fn main() {
    let matches = App::new("Tone generator")
                          .about("Generates a wav file based on frequencies and durations!")
                          .arg(Arg::with_name("out_file")
                               .short("o")
                               .long("out_file")
                               .value_name("out_file")
                               .help("specify the output file")
                               .takes_value(true)).get_matches();
    println!("{:?}", matches);
    let args: Vec<_> = env::args().collect();
    for arg in args {
        println!("{}", arg);
    }
    // TODO: Make command line parameters
	let out_file = "sine.wav";
	let sample_hz = 44_100;
    let tones = vec![(440.0, 0.25), (493.83, 0.25), (523.251, 0.25)];

	let sound: Vec<_> = tones.into_iter().map(|(freq, dur)| make_samples(dur, sample_hz, sine_wave(freq))).flatten().collect();
    write_wav_file(
        out_file, sample_hz, &quantize_samples::<i16>(&sound)
    ).expect("failed to write to file");
}
