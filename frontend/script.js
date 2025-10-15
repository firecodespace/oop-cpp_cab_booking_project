// Demo mode - works without backend
const DEMO_MODE = false;

// Demo data
let demoDrivers = [
    {id: 1, name: "Rohit", phone: "9876543210", vehicle: "Swift", registration: "DL01AB1234", type: "Sedan", rating: 4.8, available: true},
    {id: 2, name: "Amit", phone: "9876543211", vehicle: "Innova", registration: "DL02CD5678", type: "SUV", rating: 4.5, available: false}
];

let demoCustomers = [
    {id: 1, name: "Aditya", phone: "9123456789", totalRides: 5},
    {id: 2, name: "Priya", phone: "9123456788", totalRides: 3}
];

let demoRides = [
    {id: 1000, customer: "Aditya", driver: "Rohit", destination: "Connaught Place", distance: 8.5, fare: 238.5, status: "completed"},
    {id: 1001, customer: "Priya", driver: "Amit", destination: "India Gate", distance: 6.2, fare: 193.0, status: "ongoing"}
];

// Initialize the application
document.addEventListener('DOMContentLoaded', function() {
    loadCustomers();
    loadStats();
    
    // Form event listeners
    document.getElementById('driver-form').addEventListener('submit', handleAddDriver);
    document.getElementById('customer-form').addEventListener('submit', handleAddCustomer);
    document.getElementById('booking-form').addEventListener('submit', handleBookRide);
});

// Navigation functions
function showSection(sectionId) {
    // Hide all sections
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => section.classList.remove('active'));
    
    // Remove active class from all nav buttons
    const navButtons = document.querySelectorAll('.nav-btn');
    navButtons.forEach(btn => btn.classList.remove('active'));
    
    // Show selected section
    document.getElementById(sectionId).classList.add('active');
    
    // Add active class to clicked button
    event.target.classList.add('active');
    
    // Load data for specific sections
    if (sectionId === 'view-rides') {
        loadRides();
    } else if (sectionId === 'stats') {
        loadStats();
    } else if (sectionId === 'book-ride') {
        loadCustomers();
    }
}

// Driver Functions
async function handleAddDriver(event) {
    event.preventDefault();
    
    const formData = {
        id: demoDrivers.length + 1,
        name: document.getElementById('driver-name').value,
        phone: document.getElementById('driver-phone').value,
        vehicle: document.getElementById('vehicle-model').value,
        registration: document.getElementById('vehicle-reg').value,
        type: document.getElementById('vehicle-type').value,
        rating: parseFloat(document.getElementById('driver-rating').value),
        available: true
    };
    
    try {
        showLoading('driver-form');
        
        // Simulate API delay
        await new Promise(resolve => setTimeout(resolve, 1000));
        
        // Add to demo data
        demoDrivers.push(formData);
        
        showResult('driver-result', `✅ Driver ${formData.name} added successfully!`, 'success');
        document.getElementById('driver-form').reset();
        
    } catch (error) {
        showResult('driver-result', '❌ Error adding driver: ' + error.message, 'error');
    } finally {
        hideLoading('driver-form');
    }
}

// Customer Functions
async function handleAddCustomer(event) {
    event.preventDefault();
    
    const formData = {
        id: demoCustomers.length + 1,
        name: document.getElementById('customer-name').value,
        phone: document.getElementById('customer-phone').value,
        totalRides: 0
    };
    
    try {
        showLoading('customer-form');
        
        // Simulate API delay
        await new Promise(resolve => setTimeout(resolve, 1000));
        
        // Add to demo data
        demoCustomers.push(formData);
        
        showResult('customer-result', `✅ Customer ${formData.name} registered successfully!`, 'success');
        document.getElementById('customer-form').reset();
        loadCustomers(); // Refresh customer list
        
    } catch (error) {
        showResult('customer-result', '❌ Error adding customer: ' + error.message, 'error');
    } finally {
        hideLoading('customer-form');
    }
}

async function loadCustomers() {
    try {
        // In demo mode, use demo data
        updateCustomerDropdown();
    } catch (error) {
        console.error('Error loading customers:', error);
    }
}

function updateCustomerDropdown() {
    const select = document.getElementById('customer-select');
    select.innerHTML = '<option value="">Select Customer</option>';
    
    demoCustomers.forEach(customer => {
        const option = document.createElement('option');
        option.value = customer.name;
        option.textContent = `${customer.name} (${customer.phone})`;
        select.appendChild(option);
    });
}

// Ride Functions
async function handleBookRide(event) {
    event.preventDefault();
    
    const customerName = document.getElementById('customer-select').value;
    const destination = document.getElementById('destination').value;
    const distance = parseFloat(document.getElementById('distance').value);
    
    // Find available driver
    const availableDriver = demoDrivers.find(driver => driver.available);
    
    if (!availableDriver) {
        showResult('booking-result', '❌ No drivers available at the moment!', 'error');
        return;
    }
    
    try {
        showLoading('booking-form');
        
        // Simulate API delay
        await new Promise(resolve => setTimeout(resolve, 1500));
        
        // Calculate fare (₹50 base + ₹15/km)
        const fare = 50 + (distance * 15);
        
        // Create new ride
        const newRide = {
            id: demoRides.length + 1000,
            customer: customerName,
            driver: availableDriver.name,
            destination: destination,
            distance: distance,
            fare: fare,
            status: "ongoing"
        };
        
        // Add to demo data
        demoRides.push(newRide);
        
        // Mark driver as busy
        availableDriver.available = false;
        
        // Update customer ride count
        const customer = demoCustomers.find(c => c.name === customerName);
        if (customer) {
            customer.totalRides++;
        }
        
        const resultHTML = `
            <h4>🎉 Ride Booked Successfully!</h4>
            <p><strong>Ride ID:</strong> ${newRide.id}</p>
            <p><strong>Driver:</strong> ${availableDriver.name} (${availableDriver.vehicle})</p>
            <p><strong>Driver Rating:</strong> ${availableDriver.rating}/5.0 ⭐</p>
            <p><strong>Fare:</strong> ₹${fare.toFixed(2)}</p>
            <p><strong>Distance:</strong> ${distance} km</p>
            <p><strong>Destination:</strong> ${destination}</p>
            <p><strong>Status:</strong> Ride confirmed and driver is on the way!</p>
        `;
        
        document.getElementById('booking-result').innerHTML = resultHTML;
        document.getElementById('booking-result').className = 'result success';
        document.getElementById('booking-form').reset();
        
        // Update stats
        loadStats();
        
    } catch (error) {
        showResult('booking-result', '❌ Error booking ride: ' + error.message, 'error');
    } finally {
        hideLoading('booking-form');
    }
}

async function loadRides() {
    try {
        displayRides();
    } catch (error) {
        document.getElementById('rides-list').innerHTML = '<p>❌ Error loading rides: ' + error.message + '</p>';
    }
}

function displayRides() {
    const container = document.getElementById('rides-list');
    
    if (demoRides.length === 0) {
        container.innerHTML = '<p>No rides found. Book your first ride!</p>';
        return;
    }
    
    const ridesHTML = demoRides.map(ride => `
        <div class="ride-card">
            <h4>🚗 Ride #${ride.id}</h4>
            <p><strong>Customer:</strong> ${ride.customer}</p>
            <p><strong>Driver:</strong> ${ride.driver}</p>
            <p><strong>Destination:</strong> ${ride.destination}</p>
            <p><strong>Distance:</strong> ${ride.distance} km</p>
            <p><strong>Fare:</strong> ₹${ride.fare.toFixed(2)}</p>
            <p><strong>Status:</strong> <span style="color: ${ride.status === 'completed' ? 'green' : 'orange'}; font-weight: bold;">${ride.status.toUpperCase()}</span></p>
        </div>
    `).join('');
    
    container.innerHTML = ridesHTML;
}

// Statistics Functions
async function loadStats() {
    try {
        const stats = {
            totalDrivers: demoDrivers.length,
            totalCustomers: demoCustomers.length,
            activeRides: demoRides.filter(ride => ride.status === 'ongoing').length,
            totalRevenue: demoRides.reduce((sum, ride) => sum + ride.fare, 0)
        };
        updateStatsDisplay(stats);
    } catch (error) {
        console.error('Error loading statistics:', error);
    }
}

function updateStatsDisplay(stats) {
    document.getElementById('total-drivers').textContent = stats.totalDrivers || 0;
    document.getElementById('total-customers').textContent = stats.totalCustomers || 0;
    document.getElementById('active-rides').textContent = stats.activeRides || 0;
    document.getElementById('total-revenue').textContent = '₹' + (stats.totalRevenue || 0).toFixed(2);
}

// Utility Functions
function showResult(elementId, message, type) {
    const element = document.getElementById(elementId);
    element.innerHTML = message;
    element.className = `result ${type}`;
    
    // Auto-hide after 5 seconds
    setTimeout(() => {
        element.classList.remove('success', 'error');
        element.style.display = 'none';
    }, 5000);
}

function showLoading(formId) {
    document.getElementById(formId).classList.add('loading');
    const button = document.querySelector(`#${formId} button[type="submit"]`);
    button.textContent = 'Loading...';
    button.disabled = true;
}

function hideLoading(formId) {
    document.getElementById(formId).classList.remove('loading');
    const button = document.querySelector(`#${formId} button[type="submit"]`);
    
    // Reset button text based on form
    if (formId === 'driver-form') {
        button.textContent = 'Add Driver';
    } else if (formId === 'customer-form') {
        button.textContent = 'Add Customer';
    } else if (formId === 'booking-form') {
        button.textContent = 'Book Ride';
    }
    
    button.disabled = false;
}

// Auto-refresh stats every 30 seconds
setInterval(() => {
    loadStats();
}, 30000);

console.log('🚗 Smart Ride Booking System - Demo Mode Active');
console.log('📊 Current Stats:', {
    drivers: demoDrivers.length,
    customers: demoCustomers.length,
    rides: demoRides.length
});
