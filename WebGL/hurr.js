
main();

function main() {
    console.log("what");
    const canvas = document.querySelector("#glCanvas");

    const gl = canvas.getContext("webgl");
    
    if (gl === null) {
        alert("Can't init WebGL.");
        return;
    }

    gl.clearColor(0,0,0,1);
    
    gl.clear(gl.COLOR_BUFFER_BIT);
}
