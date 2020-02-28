extern crate clap;
extern crate synthrs;

use clap::{Arg, App};
use std::process;
use synthrs::synthesizer::{ make_samples, quantize_samples };
use synthrs::wave::sine_wave;
use synthrs::writer::write_wav_file;

fn main() {
    let matches = App::new("Tone generator")
                          .about("Generates a wav file based on frequencies and durations!")
                          .arg(Arg::with_name("outfile")
                               .short("o")
                               .long("outfile")
                               .value_name("outfile")
                               .help("specify the output file")
                               .takes_value(true))
                          .arg(Arg::with_name("sample rate")
                               .short("s")
                               .long("sample-rate")
                               .value_name("sample rate")
                               .help("specify the sample rate of the file")
                               .takes_value(true)).get_matches();
	let out_file = matches.value_of("outfile").unwrap_or("sine.wav");
	let sample_hz = match matches.value_of("sample rate") {
        Some(s) => match s.parse::<usize>() {
            Ok(rate) => rate,
            Err(e) => {
                println!("error: {}", e);
                process::exit(-1)
            }
        },
        None => 44_100,
    };
    let tones = vec![(440.0, 0.25), (493.83, 0.25), (523.251, 0.25)];

	let sound: Vec<_> =
        tones.into_iter()
             .map(|(freq, dur)| make_samples(dur, sample_hz, sine_wave(freq)))
             .flatten()
             .collect();

    write_wav_file(
        out_file, sample_hz, &quantize_samples::<i16>(&sound)
    ).expect("failed to write to file");
}
