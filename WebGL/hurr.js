
const mat4 = glMatrix.mat4;

const vsSrc = `
    attribute vec4 vPos;
    attribute vec4 vColor;

    uniform mat4 mvMat;
    uniform mat4 proj;

    varying lowp vec4 color;

    void main() {
        gl_Position = proj * mvMat * vPos;
        color = vColor;
    }
`;

const fsSrc = `
    varying lowp vec4 color;
    void main() {
        gl_FragColor = color;
        // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
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

function wrapBuf(buf, components, type, norm, stride, offset) {
    return {
        buffer: buf,
        num_components: components,
        type: type,
        normalize: norm,
        stride: stride,
        offset:offset,
    }
}

function initBuffs(gl) {
    let pos_buf = gl.createBuffer();
    let colo_buf = gl.createBuffer();

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

    gl.bindBuffer(gl.ARRAY_BUFFER, colo_buf);

    const colo = [
        1.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
    ];

    gl.bufferData(gl.ARRAY_BUFFER,
                  new Float32Array(colo),
                  gl.STATIC_DRAW);

    return {
        position: wrapBuf(pos_buf, 2, gl.FLOAT, false, 0, 0),
        color: wrapBuf(colo_buf, 4, gl.FLOAT, false, 0, 0),
    };
}

function bindBuf(gl, buf, attrib_location) {
    gl.bindBuffer(gl.ARRAY_BUFFER, buf.buffer);
    gl.vertexAttribPointer(
        attrib_location,
        buf.num_components,
        buf.type,
        buf.normalize,
        buf.stride,
        buf.offset);

    gl.enableVertexAttribArray(attrib_location);
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

    bindBuf(gl, bufs.position, prog_info.attribLocations.vertexPosition);
    bindBuf(gl, bufs.color, prog_info.attribLocations.vertexColor);

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
            vertexColor: gl.getAttribLocation(shader_program, 'vColor'),
        },
        uniformLocations: {
            projectionMatrix: gl.getUniformLocation(shader_program, 'proj'),
            modelViewMatrix: gl.getUniformLocation(shader_program, 'mvMat'),
        },
    };

    let bufs = initBuffs(gl);
    draw(gl, prog_info, bufs);
}
