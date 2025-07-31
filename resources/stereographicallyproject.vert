#version 330 core 
layout(location = 0) in vec4 aPos;

uniform mat4 uModel; 
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uRotation4D;  

void main() {
    // Apply 4D rotation first
    vec4 rotatedPos = uRotation4D * aPos;
    
    // Normalize the 4D point first
    vec4 normalized = normalize(rotatedPos);
    
    // Stereographic projection from north pole (0,0,0,1)
    float denom = 1.0 - normalized.w;
    vec3 projectedPos;
    
    if (abs(denom) < 0.01) {
        // Point is close to north pole, project to large circle
        projectedPos = vec3(normalized.x, normalized.y, normalized.z) * 10.0;
    } else {
        projectedPos = vec3(normalized.x, normalized.y, normalized.z) / denom;
        // Scale down to keep it reasonable
        projectedPos *= 0.5;
    }
    
    gl_Position = uProjection * uView * uModel * vec4(projectedPos, 1.0);
}