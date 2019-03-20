
const mat4 = glMatrix.mat4;
    
const vsSrc = `
    attribute vec4 vPos;

    uniform mat4 mvMat;
    uniform mat4 proj;

    void main() {
        gl_Position = proj * mvMat * vPos;
    }
`;

const fsSrc = `
    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
`;

main();

// Compile and link a full shader program
function initShaderProgram(gl, shaders) {
    let compiled_shaders = [];
    shaders.forEach(function(shader) {
        console.log(shader);

        let compiled_shader = loadShader(gl, shader.type, shader.src);
        
        compiled_shaders.push(compiled_shader);
    });

    let shader_program = gl.createProgram();
    compiled_shaders.forEach(function(shader) {
        gl.attachShader(shader_program, shader);
    });
    gl.linkProgram(shader_program);

    if (!gl.getProgramParameter(shader_program, gl.LINK_STATUS)) {
        alert('Failed to link shader program: ' + gl.getProgramInfoLog(shader_program));
        return null;
    }

    return shader_program;
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

function initBuffs(gl) {
    let pos_buf = gl.createBuffer();

    gl.bindBuffer(gl.ARRAY_BUFFER, pos_buf);
    
    const pos = [
        -1.0, 1.0,
        1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0,
    ];

    gl.bufferData(gl.ARRAY_BUFFER,
                  new Float32Array(pos),
                  gl.STATIC_DRAW);

    return {
        position: pos_buf,
    };
}

function draw(gl, prog_info, bufs) {
    gl.clearColor(0,0,0,1);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);

    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    const FoV = 45 * Math.PI / 180;
    const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
    const z_near = 0.1;
    const z_far = 100.0;
    const proj = mat4.create();

    mat4.perspective(proj, FoV, aspect, z_near, z_far);

    const mvMat = mat4.create();
    mat4.translate(mvMat, mvMat, [0.0, 0.0, -6.0]);

    const components = 2;
    const type = gl.FLOAT;
    const normalize = false;
    const stride = 0;

    const offset = 0;

    gl.bindBuffer(gl.ARRAY_BUFFER, bufs.position);
    gl.vertexAttribPointer(
        prog_info.attribLocations.vertexPosition,
        components,
        type,
        normalize,
        stride,
        offset);

    gl.enableVertexAttribArray(
        prog_info.attribLocations.vertexPosition);

    gl.useProgram(prog_info.program);

    gl.uniformMatrix4fv(
        prog_info.uniformLocations.projectionMatrix,
        false,
        proj);

    gl.uniformMatrix4fv(
        prog_info.uniformLocations.modelViewMatrix,
        false,
        mvMat);

    const vertexCount = 4;
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, vertexCount);
}

function main() {
    const canvas = document.querySelector("#glCanvas");

    const gl = canvas.getContext("webgl");

    if (gl === null) {
        alert("Can't init WebGL.");
        return;
    }

    let shaders = [
        {type: gl.VERTEX_SHADER, src: vsSrc},
        {type: gl.FRAGMENT_SHADER, src: fsSrc},
    ];

    let shader_program = initShaderProgram(gl, shaders);

    let prog_info = {
        program: shader_program,
        attribLocations: {
            vertexPosition: gl.getAttribLocation(shader_program, 'vPos'),
        },
        uniformLocations: {
            projectionMatrix: gl.getUniformLocation(shader_program, 'proj'),
            modelViewMatrix: gl.getUniformLocation(shader_program, 'mvMat'),
        },
    };

    let bufs = initBuffs(gl);
    draw(gl, prog_info, bufs);
}
