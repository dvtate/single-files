var camera, scene, renderer;
var cube;

init();
animate();

function init() {
    camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 0.01, 10 );
    camera.position.z = 1;

    scene = new THREE.Scene();
    const ambient = new THREE.AmbientLight( 0xffffff );
    scene.add( ambient );
        
    const loader = new THREE.CubeTextureLoader();
    const texture = loader.load([
    	'https://me.dvtt.net/imgs/corki.png',
    	'https://me.dvtt.net/imgs/corki.png',
    	'https://me.dvtt.net/imgs/corki.png',
      
    	'https://me.dvtt.net/imgs/corki.png',
    	'https://me.dvtt.net/imgs/corki.png',
    	'https://me.dvtt.net/imgs/corki.png',
    ]);
    const geometry = new THREE.BoxGeometry(.4, .4, .4);
    const material = new THREE.MeshLambertMaterial( {
      /* color: 0x00ff00, */
      envMap: texture,  
    });
    cube = new THREE.Mesh( geometry, material );
    scene.add( cube );
    
    renderer = new THREE.WebGLRenderer( { antialias: true } );
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( renderer.domElement );
}

function animate() {
    requestAnimationFrame( animate );
    
    cube.rotation.y += 0.02;
    cube.rotation.z += 0.005;

    renderer.render( scene, camera );
}

// TODO add point light that orbits cube
