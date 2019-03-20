
main();

// Compile and link a full shader program and return it
function initShaderProgram(gl, shaders) {
    shaders.forEach(function(el, wha) {
        console.log(el, wha);
    });
}

// Compile a single shader in a pipeline 
function loadShader(gl, type, src) {
    
    const shader = gl.createShader(type);

    gl.shaderSource(shader, src);

    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert('Compilation error on shaders: ' + gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);

        return null;
    }

    return shader;
}

function main() {
    const canvas = document.querySelector("#glCanvas");

    const gl = canvas.getContext("webgl");
    
    if (gl === null) {
        alert("Can't init WebGL.");
        return;
    }

    gl.clearColor(0,0,0,1);
    
    gl.clear(gl.COLOR_BUFFER_BIT);

    shaders = [
        {type: gl.VERTEX_SHADER, src: "uhh"},
        {type: gl.FRAGMENT_SHADER, src: "wut"}
    ];

    initShaderProgram(gl, shaders);

}
